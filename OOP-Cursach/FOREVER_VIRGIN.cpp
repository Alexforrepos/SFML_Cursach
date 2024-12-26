#include "FOREVER_VIRGIN.h"

FOREVER_VIRGIN::FOREVER_VIRGIN()
{
	NEVER = nullptr;
}

void FOREVER_VIRGIN::Update()
{
	Position = sf::Vector2f(sf::Mouse::getPosition());
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		NEVER = new LOOSE_VIRGIN();
}

void FOREVER_VIRGIN::SendMSG(MSG* msg)
{
	switch (msg->MSG_TYPE.index())
	{
	case:
	default:
		break;
	}
}

void FOREVER_VIRGIN::Draw(sf::RenderWindow& win)
{

}
