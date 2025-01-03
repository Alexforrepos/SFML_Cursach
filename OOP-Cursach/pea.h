#pragma once

#include "I_Object.h"
class pea
	: Object
{
	sf::Sprite spr;
	sf::RectangleShape shape;
	sf::Vector2f direction;
	sf::Vector2f size;


	pea(sf::Vector2f pos)
	{
		this->SetPos(pos);
		shape.setPosition(pos);
		shape.setSize({ 40,40 });
		shape.setFillColor(sf::Color::White);
	}
	int damage;
	int velocity;

public:

	// Унаследовано через I_Object
	void Update() override;
	void SendMSG(MSG* msg) override;
	void Draw(sf::RenderWindow& win) override;
};