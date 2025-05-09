#pragma once
#include "Engine/R_Manager.h"
#include "./../../Net/Client.h"

#define STANDART_PORT 11111


class MultManager
{

public:
	enum class State
	{
		WAIT_FOR_SERVER = 0, UPDATING, SHOWING, CREAITING_ROOM
	};

	struct ServerData
	{
		struct RoomData
		{ 
			std::string Name;
			bool isFull;
		};
	};

private:
	Client client;


	bool mlt_isRunning;
	State mlt_state;
	sf::Music& m_music;

public:
	void Update()
	{
		
	}

	void connect(const sf::IpAddress& ip)
	{
		client.connectToServer(ip, 11111);
	};

	void start();
	void run();
	void close();
	void handleEvent(const sf::Event& event);

	bool isRunning() const { return mlt_isRunning; }
	MultManager::State getCurrentState() const { return mlt_state; }
};

