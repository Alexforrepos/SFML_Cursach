#pragma once
#include <SFML/Graphics.hpp>
#include "I_Pos.h"
#include "I_Type.h"
#include "I_Serialize.h"
#include "MSG.h"

class Object
	: public I_Pos , public I_Type 
{
public:
	virtual void update() = 0;
	virtual void draw(sf::RenderWindow& win) = 0;
	virtual void sendMsg(MSG* msg) = 0;
};

