#pragma once
#include <SFML\Network.hpp>
#include "MSG_Manager.h"
#include <iostream>
#include "Server.h"
#include <thread>

class Client
{
	sf::TcpSocket socket;
	unsigned short serverport;
	bool isconnected = true;
	std::thread t;
	Client(unsigned short serverport,const std::string& adres)
		:socket(), serverport(serverport)
	{
		if (socket.connect(adres, serverport) != sf::Socket::Done)
		{
			throw "conection err";
		}
		isconnected = true;
	}


public:

	~Client()
	{
		isconnected = false;
		socket.disconnect();
	}

	void MSG_Send(MSG* msg)
	{
		if (!isconnected) throw "Client is not connected";
		sf::Packet p;
		p.append(msg, sizeof(msg));
		if (socket.send(p) != sf::Socket::Done)
		{
			throw "err sending msg";
		};
	}

	static Client& GetClient()
	{
		static Client d(12, "127.127.127.127");
		return d;
	}
};
