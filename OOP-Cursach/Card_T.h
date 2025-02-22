#pragma once
#include "ResourceManager.h"
#include "I_Object.h"
#include "Timer.h"
#include "gologram.h"
#include "Config_load.h"
#include "Plant.h"

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

	Card_T(sf::Vector2f pos ,PlantTypes PlT)
		:timer(200), PlT(PlT)
	{
		g = nullptr;
		shape.setPosition(pos);
		shape.setSize({ 200,200 });
		shape.setFillColor(sf::Color::Cyan);
		switch (PlT)
		{
		case Peashooter:
			shape.setTexture(&Res_Manager::get().get_access<sf::Texture>("jojo-dan.png"));
			break;
		case Sunflower:
			break;
		case MrBigPenis:
			break;
		case Repeater:
			shape.setTexture(&Res_Manager::get().get_access<sf::Texture>("loose.jpg"));
			break;
		case Showel:
			shape.setTexture(&Res_Manager::get().get_access<sf::Texture>("bozhepomogi.jpg"));
			break;
		default:
			break;
		}
		
		isactive = false;
	}
};

