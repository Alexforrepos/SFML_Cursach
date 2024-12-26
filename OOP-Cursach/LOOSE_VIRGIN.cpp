#include "LOOSE_VIRGIN.h"



void LOOSE_VIRGIN::Update()
{		
	
}

void LOOSE_VIRGIN::SendMSG(MSG* msg)
{
	switch (msg->MSG_TYPE.index())
	{
	case (int)MSG_TYPE::MSG_TYPE_CREATE:
		std::cout << "F	" << MSG_TYPE_CREATE(*msg).creator << std::endl;
		break;
	case (int)MSG_TYPE::MSG_TYPE_MOVE:
		
		break;
	default:
		break;
	}
}

void LOOSE_VIRGIN::Draw(sf::RenderWindow& win)
{
	
}


