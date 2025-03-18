#pragma once
#include "MSG.h"
#include "I_Pos.h"
#include "I_Type.h"
#include "I_Identifiable.h"
#include <SFML/Graphics.hpp>

class Object
	: public I_Pos , public I_Type , public I_Identifiable
{
	unsigned long long id;

public:

	Object() 
		: id(I_Identifiable::getId())
	{

	}

	virtual void update() = 0;
	virtual void draw(sf::RenderWindow& win) = 0;
	virtual void sendMsg(MSG* msg) = 0;

	// Унаследовано через I_Identifiable
	unsigned long long getId() override { return id; };
};

