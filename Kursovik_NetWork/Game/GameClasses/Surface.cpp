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
		//TODO::������� ��� �������� ���������� �������� �� ������� � �������
		break;
	case MSG_TYPE::MSG_TYPE_MOVE:
		//TODO::������� �������� �� ������ ���� ����� �� ����������� ������� ���� ���������
	default:
		break;
	}
}

