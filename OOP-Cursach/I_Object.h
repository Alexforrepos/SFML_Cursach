#pragma once
#include <SFML/Graphics.hpp>
#include "MSG_Manager.h"

class I_Object
{
protected:

	sf::Vector2f Position;

public:
	I_Object() = default;
	virtual void Update() = 0;
	virtual void SendMSG(MSG* msg) = 0;
	virtual void Draw(sf::RenderWindow& win) = 0;

	sf::Vector2f getPos() { return Position; }
	void SetPos(const sf::Vector2f& p) { Position = p; }
};