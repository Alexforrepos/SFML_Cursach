#pragma once
#include "I_Object.h"
#include "MSG_Manager.h"
#include <vector>

class O_Manager
{
	std::vector<I_Object*> objects;
	MSG_Manager* MSGM = MSG_Manager::get_mger();


	
public:
	O_Manager() = default;

	void add_obj(I_Object* obj) { objects.push_back(obj); };
	void clear() { MSGM->clear(); for (auto obj : objects) delete obj; objects.clear(); };
	void draw(sf::RenderWindow& win) { for (auto obj : objects)obj->Draw(win); };
	void update();
};

