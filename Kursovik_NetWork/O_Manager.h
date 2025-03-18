#pragma once
#include <SFML/Graphics.hpp>
#include "MSG_Manager.h"
#include <algorithm>
#include "Object.h"

class O_Manager
{
	std::vector<std::unique_ptr<Object>> ObjVector;

	MSG_Manager& msgm;

	O_Manager()
		: msgm(MSG_Manager::get())
	{

	}

public:

	inline static O_Manager& get()
	{
		static O_Manager inst;
		return inst;
	}
	inline void clear() 
	{ 
		ObjVector.clear(); 
	};

	void addObject(Object* obj);


	void update();
	void draw(sf::RenderWindow& win);
};

