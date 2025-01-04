#include "PlaceToPlant.h"
#include "Plant.h"


void Landing_place::GetPower(int& power)
{
	power += plant->getPrice();
}