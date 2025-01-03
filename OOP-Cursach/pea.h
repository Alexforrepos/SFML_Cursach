#pragma once

#include "I_Object.h"
class pea
	: Object
{
public:
	sf::Sprite spr;
	sf::RectangleShape shape;
	sf::Vector2f direction;

	pea(sf::Vector2f pos)
	{
		this->SetPos(pos);
		shape.setPosition(pos);
		shape.setSize({ 40,40 });
		shape.setFillColor(sf::Color::White);
	}
	int damage;
	int velocity;

	// Унаследовано через I_Object
	void Update() override;
	void SendMSG(MSG* msg) override;
	void Draw(sf::RenderWindow& win) override;
};