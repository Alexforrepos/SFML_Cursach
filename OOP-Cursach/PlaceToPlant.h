#pragma once
#define WIDTH_OF_PLACE 40.
#define BEGIN_OF_LINE_X 400.
#define BEGIN_OF_LINE_Y 400.0


class Plant;

class Landing_place
{

	bool isplacable = true, iswater = false;
	sf::Vector2f position = { 0,0 };
	sf::Vector2f Size = { WIDTH_OF_PLACE,WIDTH_OF_PLACE };
	Plant* plant = nullptr;

public:

	Landing_place(unsigned index, sf::Vector2f startpos,bool iswater)
	{
		Size = { WIDTH_OF_PLACE,WIDTH_OF_PLACE };
		this->position = startpos + sf::Vector2f{index* Size.x, index * Size.y};
		this->iswater = iswater;
		isplacable = true;
	}

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
};