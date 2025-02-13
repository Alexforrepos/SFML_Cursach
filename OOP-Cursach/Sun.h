#pragma once
#include "ResourceManager.h"
#include "I_Object.h"
#include "Timer.h"
#include "Config_load.h"
#include <math.h>

#define SUN_DIS_LEVEL_DOWN 1200
#define SUN_VALUE 25
#define SUN_VELOCITY 1	
#define SUN_START_ANGLE 1
#define SUN_TIME_TO_DIS 5000 //as ms

class Sun
	: public Object
{
	int value;
	unsigned velocity, dis_level;
	float sin_angle;
	Timer dis_time;
	bool islay;	

	sf::Sprite sprite;
public:
	Sun(const sf::Vector2f Position,const unsigned dis_lev)
		: Object(Position), value(SUN_VALUE), sin_angle(SUN_START_ANGLE), velocity(SUN_VELOCITY),
		sprite(Res_Manager::get().get_access<sf::Texture>("Sun.png")), dis_time(SUN_TIME_TO_DIS),islay(false), dis_level(dis_lev)
	{
		sprite.setPosition(Position);
		sprite.setScale(0.1, 0.1);
	}



	// Унаследовано через Object
	void Update() override;

	void SendMSG(MSG* msg) override;

	void Draw(sf::RenderWindow& win) override;;
};


