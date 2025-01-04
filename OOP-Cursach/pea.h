#pragma once
#include "ResourceManager.h"
#include "I_Object.h"
#include "Timer.h"
#include "Zombie.h"
class pea
	: Object
{
	Timer timer;
	sf::Sprite sprite;
	sf::RectangleShape shape;
	sf::Vector2f direction;
	sf::Vector2f size;

	int damage;
	int velocity;

public:
	pea(sf::Vector2f pos)
		:timer (50)
	{

		this->SetPos(pos);
		shape.setPosition(pos);
		sprite.setTexture(*Res_Manager::getmger()->get_access<sf::Texture*>("bullet.png"));
		sprite.setScale(0.2, 0.2);
	}


	int Serialize() override { return int(Serialize_Enum::Pea); }
	// Унаследовано через I_Object
	void Update() override;
	void SendMSG(MSG* msg) override;
	void Draw(sf::RenderWindow& win) override;
};