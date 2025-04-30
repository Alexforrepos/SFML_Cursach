#include "Surface.h"

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

void Surface::sendMsg(Engine::MSG* msg)
{
	switch (msg->getIndex())
	{
	case Engine::MSG_TYPE::MSG_TYPE_KILL:
		if (msg->getIndex() == Engine::MSG_TYPE::MSG_TYPE_KILL)
		{
			auto killMsg = static_cast<Engine::MSG_TYPE_KILL*>(msg);
			// Проверяем, что убита именно голограмма
			if (auto holo = dynamic_cast<Hologram*>(killMsg->victim))
			{
				sf::Vector2f pos = holo->getPos();
				for (auto& row : place_vector)
				{
					for (auto& place : row)
					{
						
						if (!place.isPlanted() &&
							place.shape_rect.getGlobalBounds().contains(pos))
						{
							
							place.plant(nullptr);      
							place.shape_rect.setTexture(
								&R_Manager::get().access<sf::Texture>("IvtClub.png"),
								true  
							);
							return;  
						}
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

void Surface::Place::deletePLant()
{
	if (!isplanted)
		return;
	isplanted = false;
	MSG_Manager::get().addMSG(std::shared_ptr<Engine::MSG>(
		new Engine::MSG_TYPE_KILL(
			plant_, // Преобразуем сырой указатель в unique_ptr
			nullptr  // Создаем новый Object как копию текущего
		)));
}


CEREAL_REGISTER_TYPE(Surface);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Object, Surface);