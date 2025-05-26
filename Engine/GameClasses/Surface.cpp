#include "Surface.h"
#include "Apex.h"
#include "PeaShooter.h"
#include "Skorostrel.h"
#include "FireLog.h"
#include "Pumpkin.h"

using namespace std;

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
		// 1) определ€ем размеры сетки
		const int rows = static_cast<int>(place_vector.size());
		const int cols = rows > 0 ? static_cast<int>(place_vector[0].size()) : 0;
		if (rows > 0 && cols > 0)
		{
			// 2) один раз инициализируем генератор и распределени€
			static std::random_device rd;
			static std::mt19937 gen(rd());
			std::uniform_int_distribution<> distRow(0, rows - 1);
			std::uniform_int_distribution<> distCol(0, cols - 1);

			// 3) выбираем случайную €чейку
			int r = distRow(gen);
			int c = distCol(gen);
			auto& cell = place_vector[r][c];

			// 4) вычисл€ем позицию в центре этой €чейки
			sf::Vector2f cellPos = cell.shape_rect.getPosition();
			sf::Vector2f cellSize = cell.shape_rect.getSize();
			sf::Vector2f sunPos{
				cellPos.x + cellSize.x / 2.f,
				cellPos.y + cellSize.y / 2.f
			};

			// 5) создаЄм и спавним Sun
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
		if (msg->getIndex() == Engine::MSG_TYPE::MSG_TYPE_KILL)
		{

			auto killMsg = dynamic_cast<Engine::MSG_TYPE_KILL*>(msg.get());
			if (!killMsg->victim) return;
			Object* obj;
			try
			{
				obj = dynamic_cast<Object*>(killMsg->victim);
				if (!obj) return;
			}
			catch (...)
			{
				return;
			}
			int type = obj->type();
			if (type == int(Types::Hologram))
			{
				Hologram* holo;
				try
				{
					holo = dynamic_cast<Hologram*>(killMsg->victim);
					if (!holo) return;
				}
				catch (...)
				{
					return;
				}

				sf::Vector2f pos = holo->getPos();

				for (auto& row : place_vector)
				{
					for (auto& place : row)
					{

						auto place_rect = sf::Rect{ place.shape_rect.getPosition().x,place.shape_rect.getPosition().y, place.shape_rect.getSize().x,place.shape_rect.getSize().y };
						auto holorect = holo->getRect();
						if (place_rect.intersects(holorect))
						{
							if (holo->getPlantType() == "Shovel" && place.isPlanted())
							{
								place.deletePLant();
								place.shape_rect.setTexture(
									&R_Manager::get().access<sf::Texture>("Drag.png"), true
								);
								return;
							}

							if (holo->getPlantType() == "Pumpkin" && place.isPlanted() && place.plantobj->getType() != "Pumpkin")
							{
								uint8_t line = static_cast<uint8_t>(&row - &place_vector[0]);
								uint8_t col = static_cast<uint8_t>(&place - &row[0]);

								auto pumpkin = make_shared<Pumpkin>(line, col);
								pumpkin->setPlant(place.plantobj);

								place.plantobj = pumpkin;
								pumpkin->setPos(place.shape_rect.getPosition());

								place.shape_rect.setTexture(
									&R_Manager::get().access<sf::Texture>("IvtClub.png"), true
								);
							}

							if (!place.isPlanted() && isInRange(holo->ObjectType, RANGE_PLANT))
							{
								auto plant = toPlant(
									holo->getPlantType(),
									static_cast<uint8_t>(&row - &place_vector[0]),  // line
									static_cast<uint8_t>(&place - &row[0])          // column
								);
								// установим позицию
								plant->setPos(place.shape_rect.getPosition());


								MSG_Manager::get().addMSG(make_shared<Engine::MSG_TYPE_CREATE>(plant, this));

								// отмечаем, что место теперь зан€то
								place.plant(plant);

							}
							/*if (!place.isPlanted())
							{
								place.plant(nullptr);
								place.shape_rect.setTexture(
									&R_Manager::get().access<sf::Texture>("IvtClub.png"), true
								);
							}*/
						}
					}
				}
			}
			if (killMsg->victim->type() == int(Types::BasePlantType) && dynamic_cast<Plant*>(killMsg->victim)->getType() == "Pumpkin")
			{
				auto pumpkin = dynamic_cast<Pumpkin*>(killMsg->victim);
				auto& place = this->place_vector[pumpkin->line][pumpkin->col];

				// ≈сли есть растение под тыквой - возвращаем его на место
				if (auto original_plant = pumpkin->getOriginalPlant()) {
					place.plantobj = original_plant;
					original_plant->setPos(place.shape_rect.getPosition());
				}
				else {
					place.plantobj.reset();
					place.isplanted = false;
					place.plantid = VOID_ID;
				}

				// ќбновл€ем текстуру клетки
				place.shape_rect.setTexture(
					&R_Manager::get().access<sf::Texture>(place.isplanted ? "IvtClub.png" : "Drag.png"), true
				);
				return;
			}

		}
		break;
	case Engine::MSG_TYPE::MSG_TYPE_MOVE:
		//TODO::сделать проверку на объект типа зомби на пересечение границы зоны проигрыша
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
	return std::shared_ptr<Object>();
}




CEREAL_REGISTER_TYPE(Surface);
CEREAL_REGISTER_TYPE(Place);
CEREAL_REGISTER_TYPE(Zombie_StartPosition);

CEREAL_REGISTER_POLYMORPHIC_RELATION(Object, Surface);