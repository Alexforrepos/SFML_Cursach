#pragma once
#include "I_Object.h"
class PlaceToPlant
	:I_Object
{
	bool isplacable = true,iswater = false;
	sf::Vector2f position = {0,0};
	I_Object* plant = nullptr;
public:
	PlaceToPlant(bool isplacable, const sf::Vector2f& position, I_Object* plant)
		: isplacable(isplacable), position(position), plant(plant)
	{
	}

	PlaceToPlant() = default;

	void SetPosition(sf::Vector2f position) { this->position = position; };
	void Move(sf::Vector2f move_vector) { this->position += move_vector; };

	void Plant(I_Object* plant) { if (isplacable)this->plant = plant; };

	void changeplacemode() { isplacable = !isplacable; }

	bool IsPlanted() { return !(plant == nullptr); }

	// Унаследовано через I_Object
	void Update() override;
	void SendMSG(MSG* msg) override;
	void Draw(sf::RenderWindow& win) override;
};