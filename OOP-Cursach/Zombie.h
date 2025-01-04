#pragma once
#include "I_Object.h"
#include "Line.h"
#include "MSG_Manager.h"
#include "ResourceManager.h"
#include "Timer.h"
class Plant;
class Zombie // обычный зомби
	:public Object
{
	Timer timer;
protected:
	int HP=100,cd_time_mc,height;
	sf::Sprite sprite;
	sf::Clock cd_time;
	sf::Vector2f damage_area_size;
	sf::Vector2f position = { 1500,400 };
	sf::Vector2f Size = { 0.18,0.18};
	std::pair<sf::Vector2f, sf::Vector2f> traectory;
	Plant* target;
	bool is_attack;

public:
    Zombie()
		:timer(100),cd_time(),damage_area_size(100,100),is_attack(false),height(0),HP(200),cd_time_mc(300)
	{
		sprite.setTexture(*Res_Manager::getmger()->get_access<sf::Texture*>("bozhepomogi.jpg"));
		sprite.setScale(0.18, 0.18);
		sprite.setPosition({ 1500,400 });
		traectory = { { 0,0 } , { 0,0 } };
	}
	
	Zombie(std::pair<sf::Vector2f, sf::Vector2f> traectory)
		:Zombie()
	{
		this->traectory = traectory;
	}
	void StartAttack(Plant &plant);   
	void StopAttack();
	// ”наследовано через Object
	virtual void Update();
	virtual void SendMSG(MSG* msg);
	int Serialize() override
	{
		return (int)Serialize_Enum::Zombie;
	}
	virtual void Draw(sf::RenderWindow& win);

	sf::FloatRect getBounds() { return { position.x,position.y,Size.x,Size.y }; }
};