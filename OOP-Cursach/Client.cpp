#include "Client.h"

using namespace std;

void Client::Handle_Host()
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
				std::cout << "Image MSG recieved" << endl;
				Get().Buff = new sf::Texture(MSG_NET_TYPE_IMG_SEND(*m).img);
				break;
			default:
				break;
			}
			delete msg;
		}
	}
}

void Client::Start(std::string IP, short port)
{
	while (!isconnected)
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
	}

	isconnected = false;
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
	delete msg;
}
