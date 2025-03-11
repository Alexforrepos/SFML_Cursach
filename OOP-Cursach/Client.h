#pragma once
#include <SFML\Network.hpp>
#include "MSG_Manager.h"
#include <iostream>
#include <thread>
#include "Game.h"

class Client
{

	sf::TcpSocket host_socket;
	std::atomic_bool isconnected;


	void HandleServer();

public:

	static Client& Get()
	{
		static Client inst;
		return inst;
	}

	void Start(sf::IpAddress ip, unsigned port);

	void SendMSG(MSG* msg);

	void Close();
};
