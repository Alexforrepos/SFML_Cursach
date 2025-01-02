#pragma once
#include "I_Object.h"
#include "gologram.h"
class Card_T
	: public Object
{
	sf::RectangleShape shape;
	bool isactive;
	Gologram* g;
public:
	

	// Унаследовано через Object
	void Update() override;

	void SendMSG(MSG* msg) override;

	void Draw(sf::RenderWindow& win) override;


	Card_T()
	{
		g = nullptr;
		shape.setPosition(200, 200);
		shape.setSize({ 200,200 });
		shape.setFillColor(sf::Color::Cyan);
		isactive = false;
	}
};

