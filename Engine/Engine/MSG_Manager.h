#pragma once
#include "MSG.h"
#include <vector>
#include <memory>

class MSG_Manager {
private:
	std::vector<std::shared_ptr<Engine::MSG>> MSGVector, Buff;
	bool isActiveUsing = false;
	MSG_Manager() = default;

public:

	void setActive() { isActiveUsing = true; }

	static MSG_Manager& get() {
		static MSG_Manager inst;
		return inst;
	}

	void addMSG(std::shared_ptr<Engine::MSG> msg)
	{
		if (!isActiveUsing)
		{
			MSGVector.emplace_back(std::move(msg));
			return;
		}
		if (msg->getIndex() == Engine::MSG_TYPE::MSG_TYPE_KILL)
			msg->getIndex();
		Buff.emplace_back(std::move(msg));
	}

	void clear() 
	{
		MSGVector.clear();
		for (auto msgs : Buff)
		{
			std::cout << "moved" << std::endl;
			MSGVector.emplace_back(std::move(msgs));
		}

		std::cout << "__________________________________" << std::endl;
		if (Buff.size() > 0)
		{
			Buff.clear();
		}
		isActiveUsing = false;
	}

	std::vector<std::shared_ptr<Engine::MSG>>& getVector() 
	{
		return MSGVector;
	}
};