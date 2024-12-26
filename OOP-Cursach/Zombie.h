#pragma once
#include "Line.h"

class Zombie // обычный зомби
	:public Object
{
protected:
	Line* line;
	int HP,cd_time_mc,height;
	sf::Sprite sprite;
	sf::Clock cd_time;
	sf::Vector2f damage_area_size;

public:

};