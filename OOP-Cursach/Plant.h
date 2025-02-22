#pragma once
#include "I_Object.h"
#include "ResourceManager.h"
#include "Config_load.h"

class Plant :
	public Object
{
	friend class Card_T;
	enum PlantCost
	{
		Peashooter = 25,
		Repeater = 50
	};

protected:
	bool isactive = false;
	bool iswater = false;
	unsigned HP, price;
	sf::Sprite sprite;
public:

	Plant(const int& HP, const int& price)
		:HP(HP), price(price), isactive(false), iswater(false)
	{
		if (Config_load::getconfig().get().at("PlantsImmortal").get<int>())
			this->HP = 100000;
	}

	Plant() = default;

	unsigned getPrice() const { return price; };

	bool IsWater() { return iswater; };

	void setActivity(bool isActive)
	{
		this->isactive = isActive;
	}

	int Serialize()
	{
		return int(Serialize_Enum::Plant);
	}

};