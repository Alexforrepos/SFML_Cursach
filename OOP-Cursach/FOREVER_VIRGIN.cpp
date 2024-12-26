#include "FOREVER_VIRGIN.h"

FOREVER_VIRGIN::FOREVER_VIRGIN()
{
	this->timeofdying.restart();
	spr.setPosition({ 400,600 });
	spr.setTexture(*Res_Manager::getmger()->get_access<sf::Texture*>("sunflower.png"));
}

void FOREVER_VIRGIN::Update()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		this->SetPos((sf::Vector2f)sf::Mouse::getPosition());
	if (timeofdying.getElapsedTime().asMilliseconds() > 5000)
		MSG_Manager::getmger()->add(new MSG(MSG_TYPE_KILL(this, this)));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
		MSG_Manager::getmger()->add(new MSG(MSG_TYPE_MOVE({ 10,10 }, this)));
}

void FOREVER_VIRGIN::SendMSG(MSG* msg)
{
	switch (msg->MSG_TYPE.index())
	{
	case (int)MSG_TYPE::MSG_TYPE_KILL:
		std::cout << "быдло получает по заслугам по указателю:" << MSG_TYPE_KILL(*msg).victim << std::endl;
		if (MSG_TYPE_KILL(*msg).victim == this)
			std::cout << "лох ебаный" << std::endl;
		MSG_Manager::getmger()->add(new MSG(MSG_TYPE_MOVE(sf::Vector2f(10, 10), this)));
		break;
	case (int)MSG_TYPE::MSG_TYPE_MOVE:
		if (MSG_TYPE_MOVE(*msg).obj == this)
		{
			this->Position += MSG_TYPE_MOVE(*msg).dir;
		}
		break;
	default:
		break;
	}
}

void FOREVER_VIRGIN::Draw(sf::RenderWindow& win)
{
	sf::RectangleShape r({ 600,200 });
	r.setFillColor(sf::Color::White);
	r.setPosition(this->Position);
	spr.setPosition(this->Position);
	win.draw(spr);
}
