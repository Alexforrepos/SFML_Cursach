#pragma once
#include "Line.h"
class WaterLine
	:public Line
{


public:
	WaterLine(int n, int size)
		: Line(n, size)
	{
		for (auto pl : places)
			pl->changewawtermode();
	}

};

