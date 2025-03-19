#pragma once

enum class Types 
	: uint8_t
{
	None = 0, Level

};



class I_Type
{
public:

	//метод который позвозяет узнать тип наследуемого объекта
	virtual int type() = 0;
};

