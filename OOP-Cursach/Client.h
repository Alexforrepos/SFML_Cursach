#pragma once
#include <SFML\Network.hpp>
#include "MSG_Manager.h"
#include <iostream>
#include "Server.h"
#include <thread>

class Client
{
	sf::TcpSocket mys;
	unsigned short serverport;

	bool isconnected = true;

	std::thread t;

	Client(unsigned short serverport,const std::string& adres)
		:mys(), serverport(serverport)
	{
		if (mys.connect(adres, serverport) != sf::Socket::Done)
		{
			throw "conection err";
		}
		isconnected = true;
	}


public:

	~Client()
	{
		isconnected = false;
		mys.disconnect();
	}

	void MSG_Send(MSG* msg)
	{
		if (!isconnected) throw "Client is not connected";
		sf::Packet p;
		p.append(msg, sizeof(msg));
		if (mys.send(p) != sf::Socket::Done)
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
