#pragma once
#include "Line.h"

class Zombie
	:public Object
{
protected:
	int surface_level = 0;
	Line* line;
	int HP;


};

