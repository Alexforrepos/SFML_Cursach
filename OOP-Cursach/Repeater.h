#pragma once
#include "Attack_Plants.h"
#include "Timer.h"
class Repeater : public Attack_Plants
{
	Timer time_to_repeat;
public:
	Repeater(sf::Vector2f pos)
		:Attack_Plants  (pos), time_to_repeat(2400)
	{
		sprite.setTexture(Res_Manager::getmger()->get_access<sf::Texture>("ps.png"));
	}
	void Update() override;
	void SendMSG(MSG* msg) override;
	void Draw(sf::RenderWindow& win) override;
};

