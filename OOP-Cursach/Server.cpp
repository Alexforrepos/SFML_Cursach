#include "Server.h"
#include "MSG_Manager.h"
#define SEND_TIME_MS 100

using namespace std;
using namespace sf;


Mutex M_1;

void SendOBJ(const std::unique_ptr<sf::TcpSocket>& clientSocket,const std::vector<I_Object*>& v)
{
	M_1.lock();
	size_t size = v.size();
	

	
	

	M_1.unlock();
}


void Server::Handle(std::unique_ptr<sf::TcpSocket> clientSocket)
{
	Clock timetosend;
	while (true)
	{
		sf::Packet p;
		if (clientSocket->receive(p) == sf::Socket::Done)
		{
			MSG_Manager::getmger()->add_buff((MSG*)p.getData());
		}
		if (timetosend.getElapsedTime().asMilliseconds() >= 100)
		{
			timetosend.restart();
			SendOBJ(clientSocket,O_Manager::getmger()->getobj());
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
