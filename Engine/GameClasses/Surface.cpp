#include "Surface.h"
#include "PeaShooter.h"
#include "Skorostrel.h"
#include "Apex.h"
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
			
			Hologram* holo;
			try
			{
				holo = dynamic_cast<Hologram*>(killMsg->victim);
				if (!holo) return;
			}
			catch(...)
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
						}

						else if (isInRange(holo->ObjectType, RANGE_PLANT) && !place.isPlanted())
							{
							auto plant = std::make_shared<Skorostrel>(
								holo->getPlantType(),
								static_cast<uint8_t>(&row - &place_vector[0]),  // line
								static_cast<uint8_t>(&place - &row[0])          // column
							);
							// установим позицию
							plant->setPos(place.shape_rect.getPosition());


							MSG_Manager::get().addMSG(make_shared<Engine::MSG_TYPE_CREATE>(plant, this));

							// отмечаем, что место теперь занято
							place.plant(plant.get());

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
			break;
	case Engine::MSG_TYPE::MSG_TYPE_MOVE:
		//TODO::сделать проверку на объект типа зомби на пересечение границы зоны проигрыша
	default:
		break;
		}
	}




	CEREAL_REGISTER_TYPE(Surface);
	CEREAL_REGISTER_TYPE(Place);
	CEREAL_REGISTER_TYPE(Zombie_StartPosition);

	CEREAL_REGISTER_POLYMORPHIC_RELATION(Object, Surface);