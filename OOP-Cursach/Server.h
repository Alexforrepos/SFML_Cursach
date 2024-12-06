#pragma once
#include <SFML/Network.hpp>
#include <thread>
#include <vector>
#include <atomic>
#include "O_Manager.h"
#include "MSG.h"


class Server
{

	std::thread t;
	
	std::atomic<std::vector<MSG*>>  togain;
	unsigned short port;

	void Handle(std::unique_ptr<sf::TcpSocket> clientSocket);
	bool isrun;
	sf::TcpListener _listener;
public:
	Server(unsigned short port)
		:port(port), _listener(), isrun()
	{

	}
	~Server()
	{
		end();
	}


	void run();

	void end();
};