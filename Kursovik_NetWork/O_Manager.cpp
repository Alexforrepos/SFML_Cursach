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

	std::vector<std::unique_ptr<Object>>::iterator it;

	for (const auto& obj : this->ObjVector)
		obj->update();

	auto msgs = msgm.getVector();

	for (const auto& msg : msgs) 
	{

		for (const auto& obj : ObjVector)
			obj->sendMsg(msg.get());

		switch (msg->getIndex()) 
		{
		case MSG_TYPE::MSG_TYPE_KILL:
			Object* objToKill = static_cast<MSG_TYPE_KILL*>(msg.get())->victim;

			// Находим объект в списке и добавляем его в "гулаг" для последующего удаления
			it = std::find(ObjVector.begin(), ObjVector.end(), objToKill);
			if (it != ObjVector.end())
			{
				gulag.push_back(it->get());  // Добавляем объект в список на удаление
			}
			break;
		case MSG_TYPE::MSG_TYPE_CREATE:

			addObject(static_cast<MSG_TYPE_CREATE*>(msg.get())->creature);
			break;
		};
	}

	for (auto objToKill : gulag)
	{
		// Ищем объект в основном списке
		auto it = std::find(ObjVector.begin(), ObjVector.end(), objToKill);
		if (it != ObjVector.end())
		{
			ObjVector.erase(it);  // Удаляем объект из основного списка
			delete objToKill;     // Освобождаем память
		}
	}

	msgm.clear();
};
