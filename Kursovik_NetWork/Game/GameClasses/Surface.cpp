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

void Surface::sendMsg(MSG* msg)
{
	switch (msg->getIndex())
	{
	case MSG_TYPE::MSG_TYPE_KILL:
		//TODO::сделать при убийстве голограмки проверку на границы и посадку
		break;
	case MSG_TYPE::MSG_TYPE_MOVE:
		//TODO::сделать проверку на объект типа зомби на пересечение границы зоны проигрыша
	default:
		break;
	}
}

std::vector<char> Surface::serialize()
{
	return std::vector<char>();
}

std::pair<Types, std::pair<void*, int>> Surface::deserialize(std::vector<char> data, size_t& readpoint)
{
	return std::pair<Types, std::pair<void*, int>>();
}

Surface& Surface::getInstance()
{
	static Surface instance;
	return instance;
}

bool Surface::isFreeField(const sf::Vector2f& pos) const {
	// Пройдитесь по местам (Place) и проверьте, содержит ли какое-либо из них точку pos и не занято ли оно
	for (const auto& line : place_vector) {
		for (const auto& place : line) {
			if (place.shape_rect.getGlobalBounds().contains(pos) && !place.isPlanted()) {
				return true;
			}
		}
	}
	return false;
}