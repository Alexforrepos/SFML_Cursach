#include "O_Manager.h"
using namespace std;


void O_Manager::update()
{
	for (auto obj : objects) obj->Update();
	this->MSGM->unique();
	auto tmpmsges = MSGM->get_msges();
	for (auto msg : tmpmsges)
	{
		switch (msg->MSG_TYPE.index())
		{
		case (int)MSG_TYPE::MSG_TYPE_MOVE:
			break;
		case (int)MSG_TYPE::MSG_TYPE_CREATE:
			break;
		case (int)MSG_TYPE::MSG_TYPE_KILL:
			break;
		default:
			break;
		}
		for (auto obj : objects)
		{
			obj->SendMSG(msg);
		}
	}
	MSGM->clear();
	MSGM->add_buff();
}
