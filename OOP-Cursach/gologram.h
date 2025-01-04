#pragma once
#include "I_Object.h"
#include "Timer.h"

enum PlantTypes
{
	Peashooter, Sunflower, MrBigPenis
};


class Gologram
	: public Object
{
	sf::RectangleShape shape;
	PlantTypes PlntTp;
	Timer timer;
public:
	Gologram(sf::Vector2f pos)
		:timer(200)
	{
		PlntTp = Peashooter;
		this->SetPos(pos);
		shape.setPosition(pos);
		shape.setSize({ 40,40 });
		shape.setFillColor(sf::Color::White);
	}
	

	// Унаследовано через Object
	void Update() override;

	void SendMSG(MSG* msg) override;

	void Draw(sf::RenderWindow& win) override;

	int Serialize() override 
	{ 
		return (int)Serialize_Enum::Hologram;
	}

	sf::Rect<float> getbound() 
	{ 
		return shape.getGlobalBounds(); 
	}
};