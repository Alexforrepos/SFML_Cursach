#include "Client.h"

void Client::Start(std::string IP, short port)
{
	auto status = this->host.connect(IP, port);
	if (status == sf::Socket::Done) 
	{
		isconnected = true;
		std::cout << "Successfully connected to Host at " << IP << ":" << port << std::endl;

		std::thread serverThread(&Client::Handle_Host);
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

void Client::SendToHost(MSG* msg)
{
	static int Try = 0;
	std::cout << "msg sending: " << Try << std::endl;
	Try++;

	if (!Get().isconnected)
	{
		std::cout << "Disconnected" << std::endl;
		return;
	}

	sf::Packet p;

	p.append((msg), sizeof(MSG));	
	if (Get().host.send(p) != sf::Socket::Done)
	{
		std::cout << "Error sending packet" << std::endl;
		Get().host.disconnect();
		Get().isconnected = false;
	}
}
