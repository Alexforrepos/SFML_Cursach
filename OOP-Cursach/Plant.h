#pragma once
#include "I_Object.h"
#include "ResourceManager.h"

class Plant :
    public Object
{
protected:
    bool iswater = false;
    unsigned HP,price;
    sf::Sprite sprite;
public:

    unsigned getPrice() const { return price; };

    bool IsWater() { return iswater; };
};