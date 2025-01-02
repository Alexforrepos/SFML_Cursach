#include "gologram.h"

void Gologram::Update()
{
	sf::Vector2f tmpdata = sf::Vector2f(sf::Mouse::getPosition());
	MSG_Manager::getmger()->add(new MSG(MSG_TYPE_MOVE(-tmpdata + Position, this)));
	SetPos(tmpdata);
	shape.setPosition(Position);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)  && timer())
	{
		MSG_Manager::getmger()->add(new MSG(MSG_TYPE_KILL(this, this)));
		timer.restart();
	}
}

void Gologram::SendMSG(MSG* msg)
{
	
}

void Gologram::Draw(sf::RenderWindow& win)
{
	win.draw(shape);
}
