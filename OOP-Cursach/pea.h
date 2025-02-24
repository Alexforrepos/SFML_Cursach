#pragma once
#include "ResourceManager.h"
#include "I_Object.h"
#include "Timer.h"
#include "Zombie.h"
class pea
	: public Object
{
protected:
	Timer timer;
	sf::Sprite sprite;
	sf::RectangleShape shape;
	sf::Vector2f direction;
	sf::Vector2f size;
	sf::Clock time_to_die;

	int damage;
	int velocity;

public:
	pea(sf::Vector2f pos)
		:timer (50),time_to_die()
	{

		this->SetPos(pos);
		shape.setPosition(pos);
		sprite.setTexture(Res_Manager::getmger()->get_access<sf::Texture>("kpst.jpg"));
		sprite.setScale(2, 2);
		size = { 100,100 };
		damage = 1;
	}

	int getDamage()  { return damage; }
	int Serialize() override { return int(Serialize_Enum::Pea); }
	sf::FloatRect GetBound() { return { Position.x,Position.y,size.x,size.y }; }
	// Унаследовано через I_Object
	void Update() override;
	void SendMSG(MSG* msg) override;
	void Draw(sf::RenderWindow& win) override;
};