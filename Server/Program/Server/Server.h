#pragma once
#include <memory>
#include "Engine/MSG.h"
#include "./../Room/Room.h"
#include <vector>
#include <SFML/Network.hpp>
#include <iostream>
#include <thread>
#include <atomic>


#define PORT1 53000
#define PORT2 53200 //ALTPORT
#define MAXROOM 10

class Server
{
public:

	enum class Status
		: uint8_t
	{
		STOPPED, WAIT_FOR_CONNECTION, NOT_READY_HANDLE
	};


	Server::Status getStatus() { return status_; }


	
public:

	static void HandleClient(sf::TcpSocket& socket) {};

private:

	Status status_;

	sf::TcpListener listener;
	sf::TcpSocket s_socket;
	
public:

	Server()
	{

	}

	~Server()
	{
		stop();
	}

	void start(const unsigned& port = PORT1) {};
	void stop() {};

	void HandleAClient(sf::TcpSocket& socket)
	{
		
	}
};