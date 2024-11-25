#include "DEBUG_CLASS.h"

using namespace std;

void DEBUG_CLASS::Update()
{
	cout << "updating debug class\n";
	MSG_Manager::get_mger()->add(new MSG(MSG_TYPE_KILL(this, this)));
}

void DEBUG_CLASS::SendMSG(MSG* msg)
{
	if (msg->MSG_TYPE.index() == (int)MSG_TYPE::MSG_TYPE_KILL)
		cout << "KILLED MSG ";
	cout << "GET MSG \n";
}

void DEBUG_CLASS::Draw(sf::RenderWindow& win)
{
	cout << "DEBUG CLASS DRAWED\n";
}
