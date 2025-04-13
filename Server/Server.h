#include <SFML/Network.hpp>
#include <iostream>
#include <thread>
#include <atomic>
#pragma once

class Server 
{
private:
    sf::TcpListener listener;
    sf::TcpSocket clientSocket;
    std::atomic<bool> isRunning;

    void clientHandler();
    void inputHandler();

public:
    bool start(unsigned short port);
    void stop();
};

class Client 
{
private:
    sf::TcpSocket socket;
    std::atomic<bool> isConnected;

    void receiveHandler();
    void inputHandler();

public:
    bool connect(const std::string& ip, unsigned short port);
    void disconnect();
};