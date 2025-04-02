#include "O_Manager.h"

using namespace std;

void O_Manager::addObject(std::shared_ptr<Object> obj) 
{
	ObjVector.push_back(std::move(obj));
}

void O_Manager::draw(sf::RenderWindow& win)
{
	for (auto& obj : ObjVector)
		obj.get()->draw(win);
}

void O_Manager::update()
{
	std::vector<Object*> gulag;
	Object* g_member = nullptr;



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
		{
			Object* objToKill = static_cast<MSG_TYPE_KILL*>(msg.get())->victim;

			// Находим объект в списке и добавляем его в "гулаг" для последующего удаления
			auto it = std::find_if(ObjVector.begin(), ObjVector.end(),
				[objToKill](const std::shared_ptr<Object>& a) {
					return (a.get()) == objToKill;
				});
			if (it != ObjVector.end())
			{
				gulag.push_back(it->get());  // Добавляем объект в список на удаление
			}
		}
		break;
		case MSG_TYPE::MSG_TYPE_CREATE:
		{
			auto* createMsg = static_cast<MSG_TYPE_CREATE*>(msg.get());
			addObject(shared_ptr<Object>(createMsg->creature)); // Теперь creature — shared_ptr
			break;
		}
		};
	}

	for (auto objToKill : gulag)
	{
		// Ищем объект в основном списке
		auto it = std::find_if(ObjVector.begin(), ObjVector.end(),
			[objToKill](const std::shared_ptr<Object>& ptr) {
				return ptr.get() == objToKill; // Сравниваем сырые указатели
			});
		if (it != ObjVector.end())
		{
			ObjVector.erase(it);  // Удаляем объект из основного списка
		}
	}

	msgm.clear();
};
