#include "Server.h"
#include <string>

bool Server::start(unsigned short port) 
{
    return true;
}

void Server::clientReadHandler() 
{
    
}

void Server::send()
{
    
}

void Server::stop() 
{
    isRunning = false;
    std::cout << "Server stopped" << std::endl;
}