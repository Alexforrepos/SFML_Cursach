#pragma once
#include "SFML/Network.hpp"
#include "MSG_Manager.h"
#include <iostream>
#include <thread>


class Host
{

	sf::TcpListener client_listener;
	sf::TcpSocket client;
	MSG_Manager& MsMg;
	std::thread handle_recieve_client;

	std::atomic<bool> isconnected;

	static void HandleClient();
	Host()
		:MsMg(MSG_Manager::get()), handle_recieve_client([&]() {Host::HandleClient(); })
	{
		
	}
public:

	bool IsStarted() { return isconnected; }

	void Send(sf::Image) {};
	void Close();
	void Start(short port);

	static Host& Get()
	{
		static Host host;
		return host;
	}
		
};

