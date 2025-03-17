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

			// ������� ������ � ������ � ��������� ��� � "�����" ��� ������������ ��������
			it = std::find(ObjVector.begin(), ObjVector.end(), objToKill);
			if (it != ObjVector.end())
			{
				gulag.push_back(it->get());  // ��������� ������ � ������ �� ��������
			}
			break;
		case MSG_TYPE::MSG_TYPE_CREATE:

			addObject(static_cast<MSG_TYPE_CREATE*>(msg.get())->creature);
			break;
		};
	}

	for (auto objToKill : gulag)
	{
		// ���� ������ � �������� ������
		auto it = std::find(ObjVector.begin(), ObjVector.end(), objToKill);
		if (it != ObjVector.end())
		{
			ObjVector.erase(it);  // ������� ������ �� ��������� ������
			delete objToKill;     // ����������� ������
		}
	}

	msgm.clear();
};
