#pragma once
#include "I_Object.h"
#define WIDTH_OF_PLACE 40.
#define BEGIN_OF_LINE_X 400.
#define BEGIN_OF_LINE_Y 400.0


class Plant;

class PlaceToPlant
	:public Object
{
	bool isplacable = true, iswater = false;
	sf::Vector2f position = { 0,0 };
	sf::Vector2f Size = { WIDTH_OF_PLACE,WIDTH_OF_PLACE };
	Plant* plant = nullptr;
public:
	PlaceToPlant(bool isplacable, const sf::Vector2f& position, Plant* plant)
		: isplacable(isplacable), position(position), plant(plant)
	{
	}

	PlaceToPlant() = default;

	PlaceToPlant(int nomer, sf::Vector2f position)
	{
		this->Size.x = WIDTH_OF_PLACE;
		this->Size.y = WIDTH_OF_PLACE;
		this->position.x = position.x + WIDTH_OF_PLACE * nomer;
		this->position.y = position.y;
		Object* plant = nullptr;
		bool isplacable = true, iswater = false;
	}

	void SetPosition(sf::Vector2f position) { this->position = position; };
	void Move(sf::Vector2f move_vector) { this->position += move_vector; };
	void Plant(Plant* plant) { if (isplacable)this->plant = plant; };

	bool changeplacemode() { return isplacable = !isplacable; }
	bool changewawtermode() { return this->iswater = !iswater; }
	bool IsPlanted() { return !(plant == nullptr); }

	void GetPower(int& power);

	// Унаследовано через I_Object
	virtual void Update();
	virtual void SendMSG(MSG* msg);
	virtual void Draw(sf::RenderWindow& win);
};