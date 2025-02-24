#pragma once
#include <SFML\Network.hpp>
#include "MSG_Manager.h"
#include <iostream>
#include <thread>

class Client
{
	sf::TcpSocket host;


	static void Handle_Host()
	{
		MSG* msg = nullptr;
		size_t received_data;

		while (!Get().isconnected)
		{
			std::this_thread::yield();
		}

		while (Get().isconnected)
		{
			sf::Packet p;
			if (Get().host.receive(p) == sf::Socket::Done)
			{
				std::cout << "recieved msg \n";
				
			}
		}
	}

	std::atomic<bool> isconnected;
	Client()
	{

	}
public:

	void Start(std::string IP, short port);
	void Close();
	static void SendToHost(MSG* msg);
	bool IsConnected() { return isconnected; }
	static Client& Get() 
	{
		static Client client;
		return client;
	}
};
