#pragma once
#include "Engine/MSG.h"
#include <string>
#include <SFML/Network.hpp>

class Client
{
	sf::TcpListener listenPort;
	sf::TcpSocket sendPort;
	
	static void HandleListenSocket();

public:

	Client();

	void connectToServer(sf::IpAddress ServerIp);
	void connectToRoom(sf::IpAddress ServerIp, uint16_t port);
	void disconnect();

	void sendMsg(Engine::MSG* msg);
	
};

