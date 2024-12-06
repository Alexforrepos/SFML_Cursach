#include "Server.h"
#include "MSG_Manager.h"
using namespace std;
using namespace sf;


void Server::Handle(std::unique_ptr<sf::TcpSocket> clientSocket)
{
	while (true)
	{
		sf::Packet p;
		if (clientSocket->receive(p) == sf::Socket::Done)
		{
			MSG_Manager::getmger()->add_buff((MSG*)p.getData());
		}
	}
}

void Server::run()
{
	isrun = true;
	while (isrun)
	{
		unique_ptr<TcpSocket> ClientSocket(new sf::TcpSocket);

		if (_listener.accept(*ClientSocket) == Socket::Done)
		{
			std::cout << "New Client with address:" << ClientSocket->getRemoteAddress() << endl;
			std::thread(&Server::Handle, this, std::move(ClientSocket)).detach();

		}
	}
	isrun = false;
	
}
