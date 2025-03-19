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
	/// <param name="data">"чистые данные"</param>
	/// <param name="readpoint">точка чтения</param>
	/// <returns>3 значения в качестве 2 пар в первой части считанный тип объекта, во втрором пара с данными и размером</returns>
	virtual std::pair<Types,std::pair<void*,int>> deserialize(std::vector<char> data, size_t& readpoint) = 0;
};