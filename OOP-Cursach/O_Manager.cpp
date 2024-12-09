#include "O_Manager.h"
using namespace std;
O_Manager* O_Manager::OMGR = nullptr;

void O_Manager::update()
{
	vector<I_Object*>::iterator it;
	for (auto obj : objects) obj->Update();
	this->MSGM->unique(); 
	for (auto msg : MSGM->get_msges())
	{
		switch (msg->MSG_TYPE.index())
		{
		case (int)MSG_TYPE::MSG_TYPE_MOVE:
			break;
		case (int)MSG_TYPE::MSG_TYPE_CREATE:
			break;
		case (int)MSG_TYPE::MSG_TYPE_KILL:
			//cout << "killing object\n";
			it = find_if(objects.begin(), objects.end(), [&](I_Object* arg)
				{ return arg == MSG_TYPE_KILL(*msg).victim; });
			if (it != objects.end())
			{
				delete* it;
				objects.erase(it);
			}
			break;
		case (int)MSG_TYPE::MSG_TYPE_DEAL_DAMAGE:
			break;
		}
		for (auto obj : objects) obj->SendMSG(msg);
		
	}
	MSGM->clear();
}