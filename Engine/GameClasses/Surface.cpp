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
		//TODO::������� ��� �������� ���������� �������� �� ������� � �������
		break;
	case Engine::MSG_TYPE::MSG_TYPE_MOVE:
		//TODO::������� �������� �� ������ ���� ����� �� ����������� ������� ���� ���������
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
			std::unique_ptr<Object>(plant_), // ����������� ����� ��������� � unique_ptr
			std::unique_ptr<Object>(nullptr)  // ������� ����� Object ��� ����� ��������
		)));
}


CEREAL_REGISTER_TYPE(Surface);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Object, Surface);