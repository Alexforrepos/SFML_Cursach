#pragma once

enum class Types 
	: uint8_t
{
	None = 0, Level

};



class I_Type
{
public:

	//����� ������� ��������� ������ ��� ������������ �������
	virtual int type() = 0;
};

