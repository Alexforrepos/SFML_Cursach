#include <iostream>
#include "Server.h"

int main()
{
	const unsigned short port = 50001;
	Server BolshieSiski;
	BolshieSiski.runTcpServer(port);
}