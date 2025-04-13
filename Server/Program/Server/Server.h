#pragma once
#include <memory>
#include "./../../../Kursovik_NetWork/Engine/MSG.h"
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
	enum
	{
		Waiting, Stopped
	} Status;
private:
	std::vector<std::unique_ptr<Room>> rooms;

	sf::TcpListener global_server_listener;
	sf::TcpSocket global_listener_socket;
	std::atomic<bool> isRunning;

	void clientReadHandler();
	void waitForClient(unsigned port)
	{
		global_server_listener.listen(port);
	};
	void send();

	Server()
		:Status(Stopped), global_server_listener(), global_listener_socket(), isRunning(true)
	{
		global_server_listener.accept(global_listener_socket);
		try
		{
			waitForClient(PORT1);
		}
		catch (...)
		{
			waitForClient(PORT2);
		}

	}
public:
	
	static Server& get()
	{
		static Server inst;
		return inst;
	}

	bool isStarted() { return isRunning; }
	bool start(unsigned short port);

	void stop();

	void run()
	{
		switch (Status)
		{
		case Server::Waiting:
			try
			{
				waitForClient(PORT1);
			}
			catch (const std::exception&)
			{
				waitForClient(PORT2);
			}
			break;
		case Server::Stopped:
			break;
		default:
			break;
		}
	};
	

};
