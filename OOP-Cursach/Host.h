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
		sf::Texture t;
		t.create(win.getSize().x, win.getSize().y);
		t.update(win);
		auto f = t.copyToImage();
		auto m = MSG(MSG_NET_TYPE_IMG_SEND(f.getPixelsPtr(), f.getSize().y * f.getSize().x * 4,f.getSize().x,f.getSize().y));
		SendMSG(m);
	};
	void Close();
	void Start(short port);

	void SendMSG(MSG& msg);
	static Host& Get()
	{
		static Host host;
		return host;
	}
		
};

