#pragma once
#include <vector>
#include "I_Type.h"

class I_Serialize
{
public:
	virtual std::vector<char> serialize() = 0;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="data">"������ ������"</param>
	/// <param name="readpoint">����� ������</param>
	/// <returns>3 �������� � �������� 2 ��� � ������ ����� ��������� ��� �������, �� ������� ���� � ������� � ��������</returns>
	virtual std::pair<Types,std::pair<void*,int>> deserialize(std::vector<char> data, size_t& readpoint) = 0;
};