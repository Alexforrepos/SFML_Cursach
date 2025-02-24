#pragma once
#include "MSG_Manager.h"
#include "I_Object.h"
#include <algorithm>
#include <vector>

class O_Manager
{
	static O_Manager* OMGR;

	std::vector<Object*> objects;
	MSG_Manager* MSGM = MSG_Manager::getmger();

public:
	static O_Manager* getmger() { return OMGR ? OMGR : OMGR = new O_Manager; }
	static void deinit() { OMGR ? delete OMGR : void(); };
	static O_Manager& get() { return OMGR ? *OMGR : *(OMGR = new O_Manager); }
	static void del() { if (OMGR) delete OMGR; }
	O_Manager() = default;
	~O_Manager()
	{
		MSGM->deinit_mger();
		for (auto objs : objects)
			delete objs;
		objects.clear();
	}

	void add_obj(Object* obj)
	{
		objects.push_back(obj); 
	};
	void clear() { MSGM->clear(); for (auto obj : objects) delete obj; objects.clear(); };
	void draw(sf::RenderWindow& win) { for (auto obj : objects)obj->Draw(win); };
	void update();

	std::vector<Object*>& getobj() { return objects; }
};