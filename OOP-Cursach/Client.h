#pragma once
#include <SFML\Network.hpp>
#include "MSG_Manager.h"
#include <iostream>
#include <thread>
#include "Game.h"

class Client
{
	sf::TcpSocket host;
	sf::Image* Buff;

	static void Handle_Host();

	std::atomic<bool> isconnected;
	Client()
		:Buff(nullptr)
	{
	}
public:

	void Start(std::string IP, short port);
	void BuffDraw(sf::RenderWindow& win)
	{
		if (!Buff)  return;
		sf::Texture t;
		t.create(Buff->getSize().x, Buff->getSize().y);
		t.loadFromImage(*Buff);
		sf::Sprite spr(t);
		spr.setPosition(0, 0);
		std::cout << "buff drawed" << std::endl;
		win.draw(spr);
	}
	void Close();
	static void SendToHost(MSG* msg);
	bool IsConnected() { return isconnected; }
	static Client& Get()
	{
		static Client client;
		return client;
	}
};
