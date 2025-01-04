#include "Attack_Plants.h"

void Attack_Plants::Update()
{
	
}

void Attack_Plants::SendMSG(MSG* msg)
{
}

void Attack_Plants::Draw(sf::RenderWindow& win)
{
	sprite.setPosition(this->Position);
	win.draw(sprite);
}
