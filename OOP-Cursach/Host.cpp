#include "Host.h"

using namespace std;

void Host::HandleClient()
{
	while (!Host::Get().isconnected)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	while (Host::Get().isconnected)
	{
		sf::Packet p;
		if (Host::Get().client.receive(p) != sf::Socket::Done)
		{

			std::cerr << "Error receiving packet from client." << std::endl;
			return;
		}

		if (p.getDataSize() < sizeof(MSG)) 
		{
			std::cerr << "Received packet size is smaller than expected." << std::endl;
			continue;
		}

		MSG* msg = (MSG*)p.getData();

		if (msg->MSG_TYPE.index() == int(MSG_TYPE::MSG_NET_TYPE_KILL_HOLO))
		{
			std::cout << "msg holo kill" << std::endl;
			std::cout << "holo kill pos: " << MSG_NET_TYPE_KILL_HOLO(*msg).pos.x << " " << MSG_NET_TYPE_KILL_HOLO(*msg).pos.y << std::endl;
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
	while (!this->isconnected)
	{
		if (client_listener.accept(client) == sf::Socket::Done)
		{
			isconnected = true;
		}
		cout << "err connect to client" << endl;
	}
	cout << "suck connect to client" << endl;
	thread t([&]() {Host::HandleClient(); });
	t.detach();
	isconnected = true;
}

void Host::SendMSG(MSG& msg)
{
	if (!isconnected)
	{
		return;
	}
	sf::Packet p;
	if (msg.MSG_TYPE.index() == int(MSG_TYPE::MSG_NET_TYPE_KILL_HOLO))
	{
		int i = 0;
		p.append(&i, sizeof(i));
		p.append(&msg, sizeof(msg));
	}
	if (msg.MSG_TYPE.index() == int(MSG_TYPE::MSG_NET_TYPE_IMG_SEND))
	{
		auto h = MSG_NET_TYPE_IMG_SEND(msg).height, w = MSG_NET_TYPE_IMG_SEND(msg).height;
		sf::Uint8* d = MSG_NET_TYPE_IMG_SEND(msg).Pixels.data();
		auto size = MSG_NET_TYPE_IMG_SEND(msg).Pixels.size();
		p.append(&h, sizeof(h));
		p.append(&w, sizeof(w));
		p.append(&size, sizeof(size));
		p.append(d, size);
	}
	if (client.send(p) != sf::Socket::Done)
	{
		std::cout << "Send MSG Err" << std::endl;
		Close();
	}
	std::cout << "send msg" << endl;
}