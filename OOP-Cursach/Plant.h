#pragma once
#include "Line.h"

class Plant :
    public Object
{
    int price;

    bool iswater = false;
    int HP;

    Line* visible;
public:
    friend class PlaceToPlant;
};
