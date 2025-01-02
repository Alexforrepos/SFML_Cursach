#pragma once

#include "I_Object.h"
class pea
	: Object
{
public:
	sf::Sprite spr;
	sf::Vector2f direction;

	
	int damage;
	int velocity;

	// Унаследовано через I_Object
	void Update() override;
	void SendMSG(MSG* msg) override;
	void Draw(sf::RenderWindow& win) override;
};	