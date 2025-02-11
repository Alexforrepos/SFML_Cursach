#pragma once
#include "ResourceManager.h"
#include "I_Object.h"
#include "Timer.h"
#include "gologram.h"
#include "Config_load.h"
//#include "Game.h"

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
		shape.setTexture(Res_Manager::get().get_access<sf::Texture*>("IvtClub.png"));
		isactive = false;
	}
};

