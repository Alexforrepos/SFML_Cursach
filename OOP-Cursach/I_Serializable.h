#pragma once
#include <iostream>
class I_Serializable
{
public:
	virtual std::pair<void*, size_t> serialize() = 0
	{
		return{ static_cast<void*>(this), sizeof(*this) };
	}
};

//���� ��������� ��� ������������ ����� ��� ���� ����� 
//��� ����������� �������� �������� �� ���� 
//������ ������ 
//
//
//
//std::pair<void*, size_t> serialize() override
//{
//	return { static_cast<void*>(this), sizeof(*this) };
//}
// 
// 
// 
// 
// 
//
