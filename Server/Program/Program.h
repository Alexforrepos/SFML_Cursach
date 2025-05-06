#pragma once
#include "./Server/Server.h"
#include "./Room/RoomManager.h"
#include "Utils/Config.h"

namespace ServerProgram
{
	class Program
	{
		bool isrun;
		Server server;
		RoomManager rm;

	public:
		Program()
			:isrun(true), server()
		{
			Config::getInstance().load("config.json");
		}

		bool isRun()
		{
			return isrun;
		}

		void run()
		{
				
			return;
		};
	};
}
