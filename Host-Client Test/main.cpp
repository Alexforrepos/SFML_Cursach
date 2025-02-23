#include <iostream>
#include "Host.h"
#include "Client.h"
#include "./../OOP-Cursach/Timer.h"
#include "I_Object.h"
#include "Test.h"

using namespace std;
int main()
{
	Timer Butt_delay(500);
	Client& cl = Client::Get();
	Host& hs = Host::Get();
	while (true)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			break;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && Butt_delay() && !Client::Get().Status())
		{
			Butt_delay.restart();
			cout << "host starting..." << endl;
			hs.Start(310);
			cout << "host started" << endl;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift) && Butt_delay() && !Host::Get().IsStarted())
		{
			Butt_delay.restart();
			cout << "Client starting..." << endl;
			cl.Start("26.117.143.176", 310);
			cout << "Client started" << endl;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && cl.Status())
		{
			cl.SendToHost(new MSG(MSG_NET_TYPE_KILL_HOLO({ 100,100 }, { 100,100 }, 1)));
		}
	};

	return 0;
}
