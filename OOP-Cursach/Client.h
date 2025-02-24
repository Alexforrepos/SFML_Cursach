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

	static void Handle_Host()
	{
		MSG* msg = nullptr;
		size_t received_data;

		while (!Get().isconnected)
		{
			std::this_thread::yield();
		}

		while (Get().isconnected)
		{
			sf::Packet p;
			if (Get().host.receive(p) == sf::Socket::Done)
			{
				//std::cout << "recieved msg \n";
				MSG* m = (MSG*)p.getData();
				switch (MSG_TYPE(m->MSG_TYPE.index()))
				{
				case MSG_TYPE::MSG_TYPE_MOVE:
					break;
				case MSG_TYPE::MSG_TYPE_KILL:
					break;
				case MSG_TYPE::MSG_TYPE_CREATE:
					break;
				case MSG_TYPE::MSG_TYPE_DEAL_DAMAGE:
					break;
				case MSG_TYPE::MSG_NET_TYPE_KILL_HOLO:
					break;
				case MSG_TYPE::MSG_NET_TYPE_IMG_SEND:
					Get().Buff = new sf::Image(m->operator MSG_NET_TYPE_IMG_SEND & ().img);
					break;
				default:
					break;
				}
				delete msg;
			}
		}
	}

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
		t.loadFromImage(*Buff);
		sf::Sprite spr(t);
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
