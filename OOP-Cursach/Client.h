#pragma once
#include <SFML\Network.hpp>
#include "MSG_Manager.h"
#include <iostream>
#include "Server.h"
#include <thread>

class Client
{
	sf::TcpSocket host;
	std::thread handle_server_thread;

	static void Handle_Server();

	std::atomic<bool> isconnected;
public:
	Client()
		:handle_server_thread([&]() { Handle_Server(); })
	{

	}

	void Start(std::string IP, short port);
	void Close();

	static Client& Get() 
	{
		static Client client;
		return client;
	}
};
