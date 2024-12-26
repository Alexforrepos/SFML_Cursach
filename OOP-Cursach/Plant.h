#pragma once
#include "Line.h"

class Plant :
    public Object
{
protected:
    bool iswater = false;
    unsigned HP,price;
    Landing_place* l_pl;
    sf::Sprite sprite;
public:
    friend class Landing_place;

};