#include "Host.h"

using namespace std;

void Host::HandleClient()
{
}

void Host::Start(unsigned port)
{
	client_socket.listen(port);
	std::cout << "Host start listen with port:" << port << std::endl;
}

void Host::WaitforClient()
{

}

void Host::Stop()
{
}

void Host::SendMsg(MSG* msg)
{
}
