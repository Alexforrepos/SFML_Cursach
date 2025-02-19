#include "O_Manager.h"
using namespace std;
O_Manager* O_Manager::OMGR = nullptr;

void O_Manager::update()
{
	vector<Object*>::iterator it;
	vector<Object*> gulag;
	for (auto obj : objects) obj->Update();
	MSGM->isvischange();
	auto msg_v = MSGM->get_msges();
	for (auto& msg : msg_v)
	{
		for (auto obj : objects) obj->SendMSG(msg);
		switch (msg->MSG_TYPE.index())
		{
		case (int)MSG_TYPE::MSG_TYPE_MOVE:
			break;
		case (int)MSG_TYPE::MSG_TYPE_CREATE:
			this->objects.push_back(MSG_TYPE_CREATE(*msg).creature);
			break;
		case (int)MSG_TYPE::MSG_TYPE_KILL:
			//cout << "killing object\n";
			it = find_if(objects.begin(), objects.end(), [&](Object* arg)
				{ return arg == MSG_TYPE_KILL(*msg).victim; });
			if (it != objects.end())
			{
				gulag.push_back(*it);
			}
			break;
		case (int)MSG_TYPE::MSG_TYPE_DEAL_DAMAGE:
			break;
		}

	}

	for (auto obj : gulag)
	{
		it = find_if(objects.begin(), objects.end(), [&](Object* arg) { return arg == obj; });
		if (it != objects.end())
		{
			delete *it;
			objects.erase(it);
		}
	}
	gulag.clear();
	MSGM->clear();
}