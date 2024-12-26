#include "PlaceToPlant.h"
#include "Plant.h"


void Landing_place::GetPower(int& power)
{
	power += plant->price;
}

void Landing_place::Update()
{
	
}

void Landing_place::SendMSG(MSG* msg)
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

void Landing_place::Draw(sf::RenderWindow& win)
{
	
}
