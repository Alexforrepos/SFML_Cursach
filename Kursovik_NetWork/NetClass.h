#pragma once
#include <SFML/Network.hpp>
#include <thread>
#include "MSG.h"
#include "Object.h"

class NetClass
{
public:
	enum class Status
		: char 
	{
		NOTISRUN = 1, ISRUN, ISHOST, ISCLINET, WAITFORCONTACT
	};
private:
	class Host
	{
		friend NetClass;
		static void HandleClient();
	private:
		sf::TcpSocket clientSocket;
		sf::TcpListener client;
	public:
		void start(unsigned port);
		void send(MSG* msg);
		void stop();
	};

	class Client
	{
		friend NetClass;
		sf::TcpSocket hostSocket;
		sf::TcpListener host;
	private:
		static void HandeHost();
	public:
		void start(sf::IpAddress ip,unsigned port);
		void send(MSG* msg);
		void stop();
	};
	Client client;
	Host host;

private:
	std::atomic<Status> status;

	NetClass()
	{

	}
public:

	static NetClass& get()
	{
		static NetClass inst;
		return inst;
	}

	void startClient();
	void stopClient();

	void send(MSG* msg);

	void startHost();
	void stopHost();


	Status getStatus();
};

