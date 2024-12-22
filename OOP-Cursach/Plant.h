#pragma once
#include "Line.h"

class Plant :
    public I_Object
{
    int prize;

    bool iswater = false;
    int HP;

    Line* visible;
public:
    friend class PlaceToPlant;
};