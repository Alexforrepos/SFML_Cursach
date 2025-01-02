#pragma once
#include <SFML/Graphics.hpp>
#include "MSG_Manager.h"

enum class Serialize_Enum{Object,Plant,Zombie,Gologram,Level};

class Object
{
protected:

	sf::Vector2f Position;
	

public:
	Object() = default;
	virtual void Update() = 0;
	virtual void SendMSG(MSG* msg) = 0;
	virtual void Draw(sf::RenderWindow& win) = 0;

	virtual int Serialize() { return 0; }

	sf::Vector2f getPos() const { return Position; }
	void SetPos(const sf::Vector2f& p) { Position = p; }
};