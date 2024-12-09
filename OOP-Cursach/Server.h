#pragma once
#include <SFML/Network.hpp>
#include <thread>
#include <vector>
#include "O_Manager.h"
#include "MSG.h"


extern sf::Mutex M_1;

class Server
{

	std::thread t;
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