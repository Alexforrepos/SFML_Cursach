#pragma once
#include "I_Object.h"
#include "Timer.h"

enum PlantTypes
{
	Peashooter, Sunflower, MrBigPenis, Repeater
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
		this->SetPos(pos);
		shape.setPosition(pos);
		shape.setSize({ 40,40 });
		shape.setFillColor(sf::Color::White);
		//PlntTp = Peashooter;
	}
	
	const PlantTypes& getType()
	{
		return PlntTp;
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