#include "O_Manager.h"

using namespace std;

void O_Manager::addObject(Object* obj)
{
	ObjVector.emplace_back(std::move(obj));
}

void O_Manager::draw(sf::RenderWindow& win)
{
	for (auto& obj : ObjVector)
		obj->draw(win);
}

void O_Manager::update()
{
	std::vector<Object*> gulag;
	Object* g_member = nullptr;

	for (auto& obj : ObjVector)
		obj->update();

	auto msgs = msgm.getVector();

	for (auto& msg : msgs)
	{
		for (auto& obj : ObjVector)
			obj->sendMsg(msg.get());
		switch (msg->getIndex())
		{

		case MSG_TYPE::MSG_TYPE_KILL:
			if (g_member = find_if(ObjVector.begin(), ObjVector.end(), [&](unique_ptr<Object>& a) {return (a.get() == static_cast<MSG_TYPE_KILL>(msg).victim); }))
		default:
			break;
		}
	}

	msgm.clear();
}