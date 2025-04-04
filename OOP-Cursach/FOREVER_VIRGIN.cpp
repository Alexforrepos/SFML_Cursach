#include "FOREVER_VIRGIN.h"

FOREVER_VIRGIN::FOREVER_VIRGIN()
{
	Position = sf::Vector2f(sf::Mouse::getPosition());
	NEVER = nullptr;
	spr.setTexture(Res_Manager::getmger()->get_access<sf::Texture>("sunflower.png"));//������� ��������
	spr.setPosition(this->Position);//������� ��������
	spr.setScale(0.1,0.1);
}

void FOREVER_VIRGIN::Update()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && NEVER == nullptr)
	{
		NEVER = new LOOSE_VIRGIN(Position);
		MSG_Manager::getmger()->add(new MSG(MSG_TYPE_CREATE(NEVER, this)));
	}
	if (NEVER != nullptr)
	{
		MSG_Manager::getmger()->add(new MSG(MSG_TYPE_MOVE(Position - sf::Vector2f(sf::Mouse::getPosition()), NEVER)));
	}
	Position = sf::Vector2f(sf::Mouse::getPosition());
	if (NEVER && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		MSG_Manager::getmger()->add(new MSG(MSG_TYPE_KILL(NEVER, this)));
		NEVER = nullptr;
	}
}

void FOREVER_VIRGIN::SendMSG(MSG* msg)
{
	switch (msg->MSG_TYPE.index())
	{
	default:
		break;
	}
}

void FOREVER_VIRGIN::Draw(sf::RenderWindow& win)
{
	spr.setPosition(this->Position);
	win.draw(spr);
}
