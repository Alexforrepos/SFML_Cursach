#pragma once
#include "./Server/Server.h"
#include "./../../Kursovik_NetWork/Game/Utils/Config.h"

class Program
{
	bool isrun;
	Server server;
public:
	Program()
		:isrun(true), server()
	{
		Config::getInstance().load("config.json");
	}

	bool isRun() { return isrun; }
	void run()
	{

	};
};

