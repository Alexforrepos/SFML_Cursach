#include "Client.h"

void Client::Handle_Server() 
{
	MSG* msg = nullptr;
	size_t received_data;

	while (!Get().isconnected)
	{
		std::this_thread::yield();
	}

	while (Get().isconnected) 
	{
		if (Get().host.receive(msg, sizeof(MSG), received_data) == sf::Socket::Done) 
		{
			MSG_Manager::get().add_buff(msg);
		}
		else 
		{

			std::cerr << "Error receiving data from Host." << std::endl;
			Get().isconnected = false;
		}
	}
}

void Client::Start(std::string IP, short port)
{
	sf::Socket::Status status = this->host.connect(IP, port);
	if (status == sf::Socket::Done) 
	{
		isconnected = true;
		std::cout << "Successfully connected to server at " << IP << ":" << port << std::endl;

		std::thread serverThread(&Client::Handle_Server);
		serverThread.detach(); 

		return;
	}

	isconnected = false;
	switch (status)
	{
	case sf::Socket::Error:
		std::cerr << "Error: Could not connect. Socket error." << std::endl;
		break;
	case sf::Socket::NotReady:
		std::cerr << "Error: Socket not ready." << std::endl;
		break;
	case sf::Socket::Partial:
		std::cerr << "Error: Connection partial, try again." << std::endl;
		break;
	case sf::Socket::Disconnected:
		std::cerr << "Error: Disconnected from server." << std::endl;
		break;
	}
}

void Client::Close()
{
	host.disconnect();
	isconnected = false;
}
