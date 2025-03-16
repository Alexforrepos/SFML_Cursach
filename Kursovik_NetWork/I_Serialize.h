#pragma once
#include <vector>


class I_Serialize
{
public:
	virtual std::vector<char> serialize() = 0;
	virtual I_Serialize* deserialize(std::vector<char> data) = 0;
};

