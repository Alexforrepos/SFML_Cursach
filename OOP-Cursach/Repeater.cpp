#include "Repeater.h"

void Repeater::Update()
{
	Attack_Plants::Update();
	if (time_to_repeat() && isactive)
	{
		pea* penis = new pea(this->Position);
		MSG_Manager::getmger()->add(new MSG(MSG_TYPE_CREATE(penis, this)));
		time_to_repeat.restart();
	}
}

void Repeater::SendMSG(MSG* msg)
{
}

void Repeater::Draw(sf::RenderWindow& win)
{
	sprite.setPosition(this->Position);
	win.draw(sprite);
}