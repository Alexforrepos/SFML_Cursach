#pragma once
#define PLACE_SEC_Y 10
#define PLACE_SEC_X 50
#define WIDTH_OF_PLACE 120.
#define BEGIN_OF_LINE_X 400.
#define BEGIN_OF_LINE_Y 400.0
#define LINE_WIDTH 1500
#define LINE_LENGTH 1500
#include <SFML/Graphics.hpp>

class Plant;

class Landing_place
{

protected:
	bool isplacable = true, iswater = false;
	sf::Vector2f position = { 0,0 };
	sf::Vector2f Size = { WIDTH_OF_PLACE,WIDTH_OF_PLACE};
	Plant* plant = nullptr;

public:

	void SetPosition(sf::Vector2f position) { this->position = position; };
	void Move(sf::Vector2f move_vector) { this->position += move_vector; };
	void Plant(Plant* plant) { if (isplacable)this->plant = plant; };

	bool ChangePlacMode(bool mode = false) { return isplacable = mode; }
	bool ChangeWaterMode(bool mode = false) { return this->iswater = mode; }

	bool IsPlanted() { return plant != nullptr; }

	void GetPower(int& power);

	void Draw(sf::RenderWindow& win)
	{

		sf::RectangleShape shape(Size);
		shape.setPosition(position);
		shape.setFillColor(isplacable ? sf::Color::Green : sf::Color::Red);
		win.draw(shape);
	}

	Landing_place(unsigned index, sf::Vector2f startpos, bool iswater)
	{
		Size = sf::Vector2f{ WIDTH_OF_PLACE,WIDTH_OF_PLACE };
		this->position = sf::Vector2f{ 10 + startpos.x + index * (Size.x  + PLACE_SEC_X), startpos.y + PLACE_SEC_Y };
		isplacable = true;
	}

	bool ison(sf::Vector2f pos)
	{
		sf::Rect<float> r{ position.x,position.y,position.x + Size.x,position.y + Size.y };
		return r.contains(pos);
	}

	sf::FloatRect getBounds() { return { position.x,position.y,Size.x,Size.y }; }
};