#pragma once
#include "./../../Engine/O_Manager.h"

class Projectile
	:public Object
{
	uint16_t
		velocity,
		line,
		damage;
	sf::Sprite spr;
public:
	Projectile(uint16_t velocity, uint16_t line, uint16_t damage,sf::Texture& texture)
		:Object(int(Types::BaseProjectileType)), velocity(velocity), line(line), damage(damage), spr(texture)
	{

	}
};

