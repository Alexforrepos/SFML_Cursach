#pragma once
#include "I_Object.h"
#include "Line.h"
#include "ResourceManager.h"

class Plant :
    public Object
{
protected:
    bool iswater = false;
    unsigned HP,price;
    Landing_place* l_pl;
    sf::Sprite sprite;
public:

    unsigned getPrice() const { return price; };

    bool IsWater();
};