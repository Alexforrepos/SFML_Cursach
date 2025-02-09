#include "Client.h"

void Client::Hande_Server()
{
	MSG* msg = nullptr;
	size_t recieved_data;

	if (!Get().isconnected) while (!Get().isconnected) {};
	while (Get().isconnected)
	{
		Get().server.receive(msg, sizeof(MSG), recieved_data);
	}

}

void Client::Start(std::string IP, short port)
{
	if (this->server.connect(IP, port) == sf::Socket::Done)
	{
		isconnected = true;
	}
}

void Client::Close()
{
	server.disconnect();	
	isconnected = false;
}
