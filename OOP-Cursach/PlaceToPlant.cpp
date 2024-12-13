#include "PlaceToPlant.h"

void PlaceToPlant::Update()
{
	
}

void PlaceToPlant::SendMSG(MSG* msg)
{
	switch (msg->MSG_TYPE.index())
	{
	case (int)MSG_TYPE::MSG_TYPE_KILL:
		if (MSG_TYPE_KILL(*msg).victim == this->plant)
			this->plant = nullptr;
		break;
	default:
		break;
	}
}

void PlaceToPlant::Draw(sf::RenderWindow& win)
{
	
}
