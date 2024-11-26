#include "O_Manager.h"
#include "DEBUG_CLASS.h"
using namespace std;

O_Manager* O_Manager::OMGR = nullptr;

void O_Manager::update()
{
	for (auto obj : objects) obj->Update();
	this->MSGM->unique(); 
	for (auto msg : MSGM->get_msges())
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
			auto it = find_if(objects.begin(), objects.end(), [&](I_Object* arg)
				{ return arg == get<MSG_TYPE_KILL>(msg->MSG_TYPE).victim; });
			if (it != objects.end())
			{
				delete* it;
				objects.erase(it);
			}
			break;
		}

	}
	MSGM->clear();
}
