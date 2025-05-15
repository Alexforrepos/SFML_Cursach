#include "O_Manager.h"

using namespace Engine;

void O_Manager::addObject(std::shared_ptr<Object> obj) {
	ObjVector.push_back(std::move(obj));
}

void O_Manager::draw(sf::RenderWindow& win) {
	for (auto& obj : ObjVector)
		obj->draw(win);
}

void O_Manager::update() {
	std::vector<std::shared_ptr<Object>> gulag;
	MSG_Manager::get().setActive();

	auto& mgr = MSG_Manager::get();

	for (const auto& obj : ObjVector)
		obj->update();

	auto msgs = msgm.getVector();

	for (const auto& msg : msgs) {

		switch (msg->getIndex())
		{
		case Engine::MSG_TYPE::MSG_TYPE_KILL: 
		{
			auto killMsg = static_cast<Engine::MSG_TYPE_KILL*>(msg.get());
			auto it = std::find_if(ObjVector.begin(), ObjVector.end(),
				[&killMsg](const auto& obj) { return obj.get() == killMsg->victim; });
			if (it != ObjVector.end()) 
			{
				gulag.push_back(*it);
			}
			if (it == ObjVector.end())
				continue;
			break;
		}
		case Engine::MSG_TYPE::MSG_TYPE_CREATE: {
			auto createMsg = static_cast<Engine::MSG_TYPE_CREATE*>(msg.get());
			addObject(createMsg->creature);
			break;
		}
		}
		for (const auto& obj : ObjVector)
			obj->sendMsg(msg);
	}

	for (const auto& obj : gulag) {
		auto it = std::find(ObjVector.begin(), ObjVector.end(), obj);
		if (it != ObjVector.end()) {
			ObjVector.erase(it);
		}
	}

	MSG_Manager::get().clear();
}