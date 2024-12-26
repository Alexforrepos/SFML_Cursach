#include "FOREVER_VIRGIN.h"

FOREVER_VIRGIN::FOREVER_VIRGIN()
{
	Position = sf::Vector2f(sf::Mouse::getPosition());
	NEVER = nullptr;
	spr.setTexture(*Res_Manager::getmger()->get_access<sf::Texture*>("sunflower.png"));//вставка текстуры
	spr.setPosition(this->Position);//позиция картинки
}

void FOREVER_VIRGIN::Update()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && NEVER == nullptr)
	{
		NEVER = new LOOSE_VIRGIN();
		O_Manager::getmger()->add_obj(NEVER);
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

}
