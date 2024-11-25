#pragma once
#include <SFML/Graphics.hpp>
#include "MSG.h"

class I_Object
{
	sf::Vector2f Position;
public:
	virtual ~I_Object() = 0;
	virtual void Update() = 0;
	virtual void SendMSG(MSG* msg) = 0;
	virtual void Draw(sf::RenderWindow& win) = 0;
};

