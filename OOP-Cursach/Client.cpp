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
		this_thread::sleep_for(chrono::milliseconds(50));
		sf::Packet p;
		if (Get().host.receive(p) == sf::Socket::Done)
		{
			int width;
			p >> width;
			if (width)
			{
				int height, size;
				p >> height >> size;
				const sf::Uint8* data = static_cast<const sf::Uint8*>(p.getData());
				/*std::vector<sf::Uint8> pixels;
				pixels.assign(data + p.getReadPosition(), data + p.getReadPosition() + size);*/
				if (Get().Buff)
					delete Get().Buff;
				Get().Buff = new sf::Image;
				Get().Buff->create(width, height, data);
			}
			if (!width)
			{
				cout << "something wrong";
			}
			
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
