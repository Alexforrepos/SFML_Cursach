#include "O_Manager.h"
using namespace std;

O_Manager* O_Manager::OMGR = nullptr;

void O_Manager::update()
{
	for (auto obj : objects) obj->Update();
	//this->MSGM->unique();
	auto tmpmsges = MSGM->get_msges();
	
	for (auto msg : tmpmsges)
	{
		for (auto obj : objects)
		{
			obj->SendMSG(msg);
		}
		switch (msg->MSG_TYPE.index())
		{
		case (int)MSG_TYPE::MSG_TYPE_MOVE:
			break;
		case (int)MSG_TYPE::MSG_TYPE_CREATE:
			break;
		case (int)MSG_TYPE::MSG_TYPE_KILL:
			cout << "killing object\n";
			auto it = find_if(objects.begin(), objects.end(), [&](auto arg)
				{return arg == get<MSG_TYPE_KILL>(msg->MSG_TYPE).victim; });
			delete (*it);
			objects.erase(it);
			break;
		}

	}
	MSGM->clear();
	MSGM->add_buff();
}
