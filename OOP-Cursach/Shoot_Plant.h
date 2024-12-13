#pragma once
#include "Plant.h"
class Shoot_Plant :
    public Plant
{
    sf::Clock lasttimeshoot;
    int cd_asmill;



public:
    virtual void Shoot() = 0;
};