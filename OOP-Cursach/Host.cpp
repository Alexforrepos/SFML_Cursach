#include "Host.h"

void Host::HandleClient()
{
	MSG* msg = nullptr;
	size_t recieved_data;
	if (!(bool)Host::Get().isconnected) 
		while (!(bool)Host::Get().isconnected) {};
	while ((bool)Host::Get().isconnected)
	{	
		if (Host::Get().client.receive(msg, sizeof(MSG*), recieved_data) == sf::Socket::Done)
		{
			Host::Get().MsMg.add_buff(msg);
		}
		
	}
}

void Host::Close()
{
	isconnected = false;
	client.disconnect();
}

void Host::Start(short port)
{
	client_listener.listen(port);
	if (client_listener.accept(client) != sf::Socket::Done)
	{
		throw "Client connection err";
	}
	isconnected = true;
}
