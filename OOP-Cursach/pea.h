#pragma once

#include "I_Object.h"
class pea
	: Object
{
	sf::Sprite spr;
	sf::Vector2f direction;
	sf::Vector2f size;

	int damage;
	int velocity;

public:

	// Унаследовано через I_Object
	void Update() override;
	void SendMSG(MSG* msg) override;
	void Draw(sf::RenderWindow& win) override;
};	