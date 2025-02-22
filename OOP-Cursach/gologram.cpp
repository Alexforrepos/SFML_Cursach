#include "gologram.h"

void Hologram::Update()
{
	sf::Vector2f tmpdata = sf::Vector2f(sf::Mouse::getPosition());
	MSG_Manager::getmger()->add(new MSG(MSG_TYPE_MOVE(-tmpdata + Position, this)));
	SetPos(tmpdata);
	spr.setPosition(Position);
	//shape.setPosition(Position);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && timer())
	{
		MSG_Manager::getmger()->add(new MSG(MSG_TYPE_KILL(this, this)));
		timer.restart();
	}
}

void Hologram::SendMSG(MSG* msg)
{

}

void Hologram::Draw(sf::RenderWindow& win)
{

	win.draw(spr);
	if (Config_load::getconfig().get().at("HitBoxVisibility").get<int>())
	{
		sf::RectangleShape s;
		s.setSize(spr.getGlobalBounds().getSize());
		s.setPosition(spr.getGlobalBounds().getPosition());
		win.draw(s);
			//win.draw();
	}
}
