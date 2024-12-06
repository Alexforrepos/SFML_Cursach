#pragma once
#include <algorithm>
#include "MSG.h"
#include "map"
#include "vector"

class MSG_Manager
{
	static MSG_Manager* MSGM_;

	std::map<int, std::vector<MSG*>> msges;
	std::vector<MSG*> buff;
public:
	MSG_Manager()
	{
		for (int i = 0; i < int(MSG_TYPE::MSG_TYPE_CREATE); i++)
		{
			msges.emplace(i,std::vector<MSG*>());
		}
	}

	void add(MSG* msg) { 
		msges.at(msg->MSG_TYPE.index()).push_back(msg);
	}
	void add_buff(MSG* msg) { buff.push_back(msg); }
	void unique();
	void konk_buff() { for (auto msg : buff) msges.at(msg->MSG_TYPE.index()).push_back(msg); };
	void exclude(MSG* msg) 
	{
		auto it = std::find(msges.at(msg->MSG_TYPE.index()).begin(), msges.at(msg->MSG_TYPE.index()).end(), msg);
		msges.at(msg->MSG_TYPE.index()).erase(it);
	};
	void clear()
	{
		for (auto &[key, msg_] : msges)
		{
			for (auto &v : msg_)
				delete v;
			msg_.clear();
		}
	};

	std::vector<MSG*> get_msges() 
	{
		std::vector<MSG*> all;
		for (auto [key, msg_t] : msges)
		{
			all.insert(all.end(), msg_t.begin(), msg_t.end());
		}
		return all; 
	};

	static MSG_Manager* getmger() { return MSGM_ ? MSGM_ : MSGM_ = new MSG_Manager; }
	static void deinit_mger() { MSGM_ ? delete MSGM_ : void(); }
};