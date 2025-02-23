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

        if (p.getDataSize() < sizeof(MSG)) {
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
	if (client_listener.accept(client) != sf::Socket::Done)
	{
		throw "Client connection err";
	}
	thread t([&]() {Host::HandleClient(); });
	t.detach();
	isconnected = true;
}
