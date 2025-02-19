#pragma once
#include "Attack_Plants.h"
class Repeater : public Attack_Plants
{
private:
	int señond_shoot_cd;
public:
	Repeater(sf::Vector2f pos)
		:Attack_Plants  (pos)
	{
		
	}
};

