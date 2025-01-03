#pragma once
#include "I_Object.h"
#include "Line.h"

class Zombie // обычный зомби
	:public Object
{
protected:
	int HP,cd_time_mc,height;
	sf::Sprite sprite;
	sf::Clock cd_time;
	sf::Vector2f damage_area_size;
	std::pair<sf::Vector2f, sf::Vector2f> traectory;
	bool is_attack;

public:
	
	Zombie(std::pair<sf::Vector2f, sf::Vector2f> traectory)
	{

	}

	// ”наследовано через Object
	virtual void Update();
	 
	virtual void SendMSG(MSG* msg);

	virtual void Draw(sf::RenderWindow& win);

	
};