#pragma once
#include "MSG.h"
#include "vector"

class MSG_Manager
{
	static MSG_Manager* MSGM;

	std::vector<MSG*> msges,buff;

public:
	void add(MSG* msg) { msges.push_back(msg); }
	void add_buff(MSG* msg) { buff.push_back(msg); }
	void unique();
	void clear() { for (auto msg : msges)delete msg; msges.clear(); };
	void exclude(MSG* msg);
	void add_buff() { msges.insert(msges.end(), buff.begin(), buff.end()); };

	const std::vector<MSG*>& get_msges() { return msges; };

	static MSG_Manager* get_mger() { return MSGM ? MSGM : MSGM = new MSG_Manager; }
	static void deinit_mger() { MSGM ? delete MSGM : void(); }
};