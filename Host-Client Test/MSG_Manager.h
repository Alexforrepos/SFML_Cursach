#pragma once
#include <algorithm>
#include "vector"
#include "MSG.h"
#include "map"

class MSG_Manager
{
	static MSG_Manager* MSGM_;

	std::map<int, std::vector<MSG*>> msges;
	std::vector<MSG*> buff;

	bool isvis;
public:
	MSG_Manager()
	{
		for (int i = 0; i <= int(MSG_TYPE::MSG_TYPE_DEAL_DAMAGE); i++)
		{
			msges.emplace(i,std::vector<MSG*>());
		}
		isvis = false;
	}
	void Recieve(MSG* msg) { this->buff.push_back(msg); };
	void add(MSG* msg) 
	{ 
		if (!isvis)
		{
			msges.at(msg->MSG_TYPE.index()).push_back(msg);
			return;
		}
		add_buff(msg);
	}
	void isvischange() { isvis = true; }
	void add_buff(MSG* msg) { buff.push_back(msg); };
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
		isvis = false;
		for (auto msg : buff)
			add(msg);
		buff.clear();
	};
	std::vector<MSG*> get_msges() 
	{
		std::vector<MSG*> all;
		for (auto &[key, msg_t] : msges)
		{
			all.insert(all.end(), msg_t.begin(), msg_t.end());
		}
		return all; 
	};
	static MSG_Manager* getmger() { return MSGM_ ? MSGM_ : MSGM_ = new MSG_Manager; }
	static void deinit_mger() { MSGM_ ? delete MSGM_ : void(); }
	static MSG_Manager& get() { return MSGM_ ? *MSGM_ : *(MSGM_ = new MSG_Manager); }
	static void del() { if (MSGM_) delete MSGM_; }
};	