#pragma once
#include "I_Object.h"
#include "Timer.h"
class Gologram
	: public Object
{
	sf::RectangleShape shape;
	Timer timer;
public:
	Gologram(sf::Vector2f pos)
		:timer(200)
	{
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
		return (int)Serialize_Enum::Gologram;
	}

	sf::Rect<float> getbound() 
	{ 
		return shape.getGlobalBounds(); 
	}
};