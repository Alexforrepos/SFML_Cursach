#pragma once
#include "I_Object.h"
class Gologram
	: public Object
{
	sf::RectangleShape shape;
	
public:
	Gologram(sf::Vector2f pos)
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

	int Serialize() override { return (int)Serialize_Enum::Gologram; }

	sf::Rect<float> getbound() { return shape.getGlobalBounds(); }
};

