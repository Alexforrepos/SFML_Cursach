#pragma once
#include "I_Object.h"
#include "MSG_Manager.h"
#include "ResourceManager.h"


class Primer
	: public Object
{
public:
	Primer();

	// Унаследовано через I_Object
	sf::Sprite spr;

	sf::Clock timeofdying;
	// Унаследовано через I_Object
	void Update() override;

	void SendMSG(MSG* msg) override;

	void Draw(sf::RenderWindow& win) override;

};

