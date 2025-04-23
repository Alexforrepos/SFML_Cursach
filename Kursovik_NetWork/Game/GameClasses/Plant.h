#pragma once
#include "./../../Engine/O_Manager.h"

class Plant
	: public Object
{
public:
	
	~Plant() = default;
private:
	uint8_t line, col;
	uint16_t HP;


public:
	Plant() = default;

	Plant(const uint8_t& line, const uint8_t& col, const uint16_t& HP)
		:Object(int(Types::BasePlantType)), line(line), col(col), HP(HP)
	{
	}
};
