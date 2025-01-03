#pragma once
#include "I_Object.h"
#include "Line.h"
#include "MSG_Manager.h"
#include "ResourceManager.h"
#include "Timer.h"
class Zombie // ������� �����
	:public Object
{
	Timer timer;
protected:
	int HP,cd_time_mc,height;
	sf::Sprite sprite;
	sf::Clock cd_time;
	sf::Vector2f damage_area_size;
	std::pair<sf::Vector2f, sf::Vector2f> traectory;
	bool is_attack;

public:
    Zombie()
		:timer(100)
	{
		sprite.setTexture(*Res_Manager::getmger()->get_access<sf::Texture*>("bozhepomogi.jpg"));
		sprite.setScale(0.18, 0.18);
		sprite.setPosition({ 1500,400 });
		
	}

	// ������������ ����� Object
	virtual void Update();
	 
	virtual void SendMSG(MSG* msg);

	virtual void Draw(sf::RenderWindow& win);

	
};