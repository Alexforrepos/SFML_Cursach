#include "Surface.h"
#include "Apex.h"
#include "PeaShooter.h"
#include "Skorostrel.h"
#include "FireLog.h"
#include "Pumpkin.h"
#include "IceP.h"
#include "SunFlower.h"
using namespace std;

void Surface::setZombie(std::shared_ptr<Object> zombie)
{
	auto zmb = dynamic_cast<Zombie*>(zombie.get());
	if (!zmb)
	{
		std::cout << "ist not zombie its vibladok\n";
		return;
	}
	zmb->setPos(this->zombie_places[zmb->getLine()].shape_rect.getPosition());
}

sf::Vector2f Surface::getPos()
{
	//NULL
	return sf::Vector2f();
}

void Surface::changePos(const sf::Vector2f& other)
{
	//NULL
}

void Surface::setPos(sf::Vector2f other)
{
	//NULL
}

void Surface::update()
{
	if (sunSpawnTimer())
	{
		const int rows = static_cast<int>(place_vector.size());
		const int cols = rows > 0 ? static_cast<int>(place_vector[0].size()) : 0;
		if (rows > 0 && cols > 0)
		{			static std::random_device rd;
			static std::mt19937 gen(rd());
			std::uniform_int_distribution<> distRow(0, rows - 1);
			std::uniform_int_distribution<> distCol(0, cols - 1);

			
			int r = distRow(gen);
			int c = distCol(gen);
			auto& cell = place_vector[r][c];

			sf::Vector2f cellPos = cell.shape_rect.getPosition();
			sf::Vector2f cellSize = cell.shape_rect.getSize();
			sf::Vector2f sunPos{
				cellPos.x + cellSize.x / 2.f,
				cellPos.y + cellSize.y / 2.f
			};

			auto& tex = R_Manager::get().access<sf::Texture>("Sun.png");
			auto sun = std::make_shared<Sun>(sunPos, tex);
			MSG_Manager::get().addMSG(
				std::make_shared<Engine::MSG_TYPE_CREATE>(sun, this)
			);
		}

		sunSpawnTimer.restart();
	}
}

void Surface::draw(sf::RenderWindow& win)
{
	for (auto& line : place_vector)
	{
		win.draw(this->line(line));
		for (auto place : line)
			place.draw(win);
	}
	for (auto& zp : zombie_places)
	{
		win.draw(zp.shape_rect);
	}
}



void Surface::sendMsg(const std::shared_ptr<Engine::MSG>& msg)
{
	switch (msg->getIndex())
	{
	case Engine::MSG_TYPE::MSG_TYPE_KILL:
	{
		auto killMsg = dynamic_cast<Engine::MSG_TYPE_KILL*>(msg.get());
		if (!killMsg || !killMsg->victim)
			return;

		// Обрабатываем попадание Hologram-а (шаблон для посадки/лопаты/тыквы)
		if (killMsg->victim->type() == int(Types::Hologram))
		{
			auto holo = dynamic_cast<Hologram*>(killMsg->victim);
			if (!holo)
				return;

			sf::Vector2f pos = holo->getPos();

			for (auto& row : place_vector)
			{
				for (auto& place : row)
				{
					sf::FloatRect place_rect{
						place.shape_rect.getPosition().x,
						place.shape_rect.getPosition().y,
						place.shape_rect.getSize().x,
						place.shape_rect.getSize().y
					};
					sf::FloatRect holoRect = holo->getRect();

					if (place_rect.intersects(holoRect))
					{
						// 1) Лопата: удаляем растение
						if (holo->getPlantType() == "Shovel" && place.isPlanted())
						{
							place.deletePLant();
							place.shape_rect.setTexture(
								&R_Manager::get().access<sf::Texture>("Drag.png"), true
							);
							return;
						}

						// 2) Тыква: оборачиваем растение в Pumpkin
						if (holo->getPlantType() == "Pumpkin"
							&& place.isPlanted()
							&& place.plantobj->getType() != "Pumpkin")
						{
							uint8_t line = static_cast<uint8_t>(&row - &place_vector[0]);
							uint8_t col = static_cast<uint8_t>(&place - &row[0]);

							auto pumpkin = std::make_shared<Pumpkin>(line, col);
							pumpkin->setPlant(place.plantobj);

							place.plantobj = pumpkin;
							pumpkin->setPos(place.shape_rect.getPosition());

							place.shape_rect.setTexture(
								&R_Manager::get().access<sf::Texture>("pumpkin.png"), true
							);
							return;
						}

						// 3) Посадка нового растения
						if (!place.isPlanted() && isInRange(holo->ObjectType, RANGE_PLANT))
						{
							auto plant = toPlant(
								holo->getPlantType(),
								static_cast<uint8_t>(&row - &place_vector[0]),  // line
								static_cast<uint8_t>(&place - &row[0])          // column
							);

							plant->setPos(place.shape_rect.getPosition());

							MSG_Manager::get().addMSG(
								std::make_shared<Engine::MSG_TYPE_CREATE>(plant, this)
							);

							place.plant(plant);

							// <-- Вот здесь: сразу выходим из метода,
							// чтобы не посадить растение в соседнюю клетку
							return;
						}
					}
				}
			}
		}

		// Обработка уничтожения Pumpkin — восстанавливаем оригинал или очищаем клетку
		if (killMsg->victim->type() == int(Types::BasePlantType)
			&& dynamic_cast<Plant*>(killMsg->victim)->getType() == "Pumpkin")
		{
			auto pumpkin = dynamic_cast<Pumpkin*>(killMsg->victim);
			auto& place = this->place_vector[pumpkin->line][pumpkin->col];

			if (auto original_plant = pumpkin->getOriginalPlant()) {
				place.plantobj = original_plant;
				original_plant->setPos(place.shape_rect.getPosition());
			}
			else {
				place.plantobj.reset();
				place.isplanted = false;
				place.plantid = VOID_ID;
			}

			place.shape_rect.setTexture(
				&R_Manager::get().access<sf::Texture>(
					place.isplanted ? "IvtClub.png" : "Drag.png"
				),
				true
			);
			return;
		}
	}
	break;
	case Engine::MSG_TYPE::MSG_TYPE_MOVE: {
		auto mv = std::dynamic_pointer_cast<Engine::MSG_TYPE_MOVE>(msg);
		if (!mv) return;

		// трогаем только зомби
		if (mv->target->type() != int(Types::BaseZombieType))
			return;

		auto zmb = dynamic_cast<Zombie*>(mv->target.get());
		if (!zmb) return;

		unsigned row = zmb->getLine();
		float zx = zmb->getPos().x;

		// ищем первую клетку в этом ряду с посаженным растением
		for (auto& place : place_vector[row]) 
		{
			if (place.isPlanted()) {
				float px = place.shape_rect.getPosition().x;
				float pw = place.shape_rect.getSize().x;
				// если зомби «зашёл» в границу клетки
				if (zx <= px + pw && zx > px) 
				{
					// назначаем цель и выходим
					zmb->setAttackTarget(place.plantobj);
					return;
				}
			}
		}

		// если ни с кем не столкнулись — сбрасываем цель (на случай, если растение сгнило)
		zmb->setAttackTarget(nullptr);
	} break;
	case Engine::MSG_TYPE::MSG_TYPE_CREATE:
	{
		auto msg_create = dynamic_cast<Engine::MSG_TYPE_CREATE*>(msg.get());
		if (!msg_create || msg_create->creature->type() != int(Types::BaseZombieType))
			return;
		this->setZombie(msg_create->creature);

	}
	break;
	default:
		break;
	}
}

std::shared_ptr<Object> Surface::toPlant(std::string plantType, uint8_t line, uint8_t col)
{
	if (plantType == "PeaShooter")
	{
		return make_shared<PeaShooter>(line, col);
	}
	else if (plantType == "Apex")
	{
		return make_shared<Apex>(line, col);
	}
	else if (plantType == "FireLog")
	{
		return make_shared<FireLog>(line, col);
	}
	else if (plantType == "Pumpkin")
	{
		return make_shared<Pumpkin>(line, col);

	}
	else if (plantType == "IceP")
	{
		return make_shared<IceP>(line, col);

	}
	else if (plantType == "SunFlower") {
		return make_shared<SunFlower>(line, col);
	}
	else if (plantType == "Skorostrel")
	{
		return make_shared<Skorostrel>(line, col);

	}
	return shared_ptr<Object>();
}


 