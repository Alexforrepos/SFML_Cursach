#pragma once
#include "I_Object.h"
#include "ResourceManager.h"

class Plant :
    public Object
{
protected:
    bool isActive;
    bool iswater = false;
    unsigned HP,price;
    sf::Sprite sprite;
public:

    unsigned getPrice() const { return price; };

    bool IsWater() { return iswater; };

    void setActivity(bool isActive)
    {
        this->isActive = isActive;
        //eto sssettterrr
    }

};