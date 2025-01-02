#pragma once
#include "Line.h"
#include "I_Object.h"

class Zombie // обычный зомби
	:public Object
{
protected:
	int HP,cd_time_mc,height;
	sf::Sprite sprite;
	sf::Clock cd_time;
	sf::Vector2f damage_area_size;

public:

};