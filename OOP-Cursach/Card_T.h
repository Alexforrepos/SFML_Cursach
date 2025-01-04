#pragma once
#include "I_Object.h"
#include "Timer.h"
#include "gologram.h"

enum PlantTypes
{
	Peashooter, Sunflower, MrBigPenis
};

class Card_T
	: public Object
{
	sf::RectangleShape shape;
	bool isactive;
	PlantTypes PlT;
	Gologram* g;
	Timer timer;
public:
	

	// Унаследовано через Object
	void Update() override;

	void SendMSG(MSG* msg) override;

	void Draw(sf::RenderWindow& win) override;

	PlantTypes getType()
	{
		return PlT;
	}

	Card_T()
		:timer(200)
	{
		PlT = Peashooter;
		g = nullptr;
		shape.setPosition(200, 200);
		shape.setSize({ 200,200 });
		shape.setFillColor(sf::Color::Cyan);
		isactive = false;
	}
};

