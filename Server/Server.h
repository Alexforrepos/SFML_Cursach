#include <SFML/Network.hpp> 
#include <iostream>
#pragma once
class Server
{
private:
public:
    void runTcpServer(unsigned short port); 
    void createConnection(unsigned short port, sf::TcpListener listener);
    void sendInfo(unsigned short port, sf::TcpListener listener, sf::TcpSocket socket);
    void getInfo(unsigned short port, sf::TcpListener listener, sf::TcpSocket socket);
};