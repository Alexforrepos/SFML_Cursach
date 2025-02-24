#pragma once
#include "pea.h"
class IcePea : public pea
{
	IcePea(sf::Vector2f pos)
		:pea(pos)
	{
		this->SetPos(pos);
		shape.setPosition(pos);
		sprite.setTexture(Res_Manager::getmger()->get_access<sf::Texture>("icepea.jpg"));
		sprite.setScale(0.5, 0.4);
		size = { 100,100 };
		damage = 1;
	}
	void Update();
	void SendMSG(MSG* msg);
};
