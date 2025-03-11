#pragma once
#include "MSG.h"
#include <vector>
#include <memory>

//
//пример добавления сообщения в обработку
//MSG_Manager::get().addMSG(new MSG_TYPE_MOVE({123,123},this))
//


class MSG_Manager
{

	std::vector<std::unique_ptr<MSG>> MSGVector;
	
	MSG_Manager() = default;

public:
	
	static MSG_Manager& get()
	{
		static MSG_Manager inst;
		return inst;
	}

	void addMSG(MSG* msg) 
	{
		MSGVector.emplace_back(std::move(msg));
	};

	void clear() 
	{
		MSGVector.clear();
	};

	std::vector<std::unique_ptr<MSG>>& getVector() 
	{
		return MSGVector; 
	};
};