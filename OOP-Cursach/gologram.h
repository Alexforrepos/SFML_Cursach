#pragma once
#include "I_Object.h"
#include "Timer.h"
#include "ResourceManager.h"
#include "Config_load.h"
enum HoloType

{
	Peashooter, Sunflower, MrBigPenis, Repeater, Showel
};


class Hologram
	: public Object
{
	HoloType PlntTp;
	sf::Sprite spr;
	Timer timer;
public:
	Hologram(sf::Vector2f pos, HoloType type)
		:timer(200), PlntTp(type), spr(Res_Manager::get().get_access<sf::Texture>("Seed.png"))
	{
		this->SetPos(pos);
		spr.setScale(0.1, 0.1);
		if (type == Showel)
		{
			spr.setTexture(Res_Manager::get().get_access<sf::Texture>("showel.png"),true);
			spr.setScale(0.05, 0.05);
		}
	}

	const HoloType& getType()
	{
		return PlntTp;
	}

	// Унаследовано через Object
	void Update() override;

	void SendMSG(MSG* msg) override;

	void Draw(sf::RenderWindow& win) override;

	int Serialize() override
	{
		return (int)Serialize_Enum::Hologram;
	}

	sf::Rect<float> getbound()
	{
		return spr.getGlobalBounds();
	}
};