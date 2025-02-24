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
		:MsMg(MSG_Manager::get())
	{
		
	}
public:
	bool IsStarted() { return isconnected; }

	void SendWindow(sf::RenderWindow& win) 
	{ 
		sf::RenderTexture r;
		r.create(win.getSize().x, win.getSize().y);
		SendMSG(MSG(MSG_NET_TYPE_IMG_SEND(r.getTexture())));  
	};
	void Close();
	void Start(short port);

	void SendMSG(const MSG& msg);
	static Host& Get()
	{
		static Host host;
		return host;
	}
		
};

