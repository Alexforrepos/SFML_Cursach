#include "Server.h"
#include <string>

bool Server::start(unsigned short port) 
{
    
}

void Server::clientReadHandler() 
{
    
}

void Server::send()
{
    global_server_listener
}

void Server::stop() 
{
    isRunning = false;
    clientSocket.disconnect();
    listener.close();
    std::cout << "Server stopped" << std::endl;
}

