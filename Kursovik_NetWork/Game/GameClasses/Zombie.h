#pragma once
#include "./../../Engine/O_Manager.h"


class Zombie
	: public Object
{
	sf::Vector2f pos;

	uint16_t HP,
		velocity, // =speed 
		damage,
		line;

	sf::Sprite spr;
public:

	Zombie(const uint16_t& HP, const uint16_t& velocity, const uint16_t& damage, const uint16_t& line, const sf::Sprite& spr)
		:Object(int(Types::BaseZombieType)), HP(HP), velocity(velocity), damage(damage), line(line), spr(spr)
	{
		
	}

	sf::Vector2f getPos() { return pos; }
	sf::Vector2f setPos(const sf::Vector2f& pos) { this->pos = pos; }
	
};
