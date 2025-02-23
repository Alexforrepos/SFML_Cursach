#include "Host.h"

using namespace std;

void Host::HandleClient()
{
	
	while (!(bool)Host::Get().isconnected) {};
	std::cout << "Connected...\n";
	while ((bool)Host::Get().isconnected)
	{
		sf::Packet p;
		if (Host::Get().client.receive(p) == sf::Socket::Done)
		{
			MSG* msg = (MSG*)p.getData();
			if (msg->MSG_TYPE.index() == int(MSG_TYPE::MSG_NET_TYPE_KILL_HOLO))
			{
				cout << "msg holo kill" << endl;
				cout << "holo kill pos:" << MSG_NET_TYPE_KILL_HOLO(*msg).pos.x << " " << MSG_NET_TYPE_KILL_HOLO(*msg).pos.x << endl;
			}
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
