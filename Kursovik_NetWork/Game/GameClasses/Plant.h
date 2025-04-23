#pragma once
#include "./../../Engine/O_Manager.h"

class Plant
	: public Object
{
public:

private:
	uint8_t line, col;
	uint16_t HP;


public:
	Plant() = default;

	Plant(const uint8_t& line, const uint8_t& col, const uint16_t& HP)
		:Object(int(Types::BasePlantType)), line(line), col(col), HP(HP)
	{
	}

	template <class Archive>
	void serialize(Archive& ar) {
		ar& cereal::base_class<Object>(this);  // Сериализация Object
		ar(line,col,HP);  // Сериализация полей Plant
	}

	virtual ~Plant() = default;	
};
