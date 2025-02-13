#include "Primer.h"

Primer::Primer()
{
	this->timeofdying.restart();
	spr.setPosition({ 300,300 });
	spr.setTexture(Res_Manager::getmger()->get_access<sf::Texture>("00_6.png"));
}

void Primer::Update()
{

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		this->SetPos((sf::Vector2f)sf::Mouse::getPosition());
	if (timeofdying.getElapsedTime().asMilliseconds() > 5000)
		MSG_Manager::getmger()->add(new MSG(MSG_TYPE_KILL(this, this)));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
		MSG_Manager::getmger()->add(new MSG(MSG_TYPE_MOVE({ 10,10 }, this)));
	
}

void Primer::SendMSG(MSG* msg)
{
	switch (msg->MSG_TYPE.index())
	{
	case (int)MSG_TYPE::MSG_TYPE_KILL:
		std::cout << "бл€ убивают чувака по указателю:" << MSG_TYPE_KILL(*msg).victim << std::endl;
		if (MSG_TYPE_KILL(*msg).victim == this)
			std::cout << "так это ж € бл€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€!" << std::endl;
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

void Primer::Draw(sf::RenderWindow& win)
{
	sf::RectangleShape r({ 300,300 });
	r.setFillColor(sf::Color::White);
	r.setPosition(this->Position);
	spr.setPosition(this->Position);
	win.draw(spr);
}

