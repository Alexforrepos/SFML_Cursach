#pragma once
#include "SFML/Network.hpp"
#include "MSG_Manager.h"
#include <iostream>
#include <thread>


class Host
{
	sf::TcpListener client_socket;
	std::atomic_bool isconnected;

	void HandleClient();

public:

	static Host& Get() 
	{
		static Host inst;
		return inst;
	}

	void Start(unsigned port);
	void WaitforClient();
	void Stop();
	void SendMsg(MSG* msg);
	
};

