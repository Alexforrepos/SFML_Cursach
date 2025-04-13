#pragma once
#include "./../Kursovik_NetWork/Engine/MSG.h"
#include <vector>
#include "Room.h"
#include <SFML/Network.hpp>
#include <iostream>
#include <thread>
#include <atomic>


#define PORT1 53000
#define PORT2 53200 

class Server 
{
private:
    std::vector<Room> rooms;

    sf::TcpListener global_server_listener;
    std::atomic<bool> isRunning;

    void clientReadHandler();
    void waitForClinet();
    void send();

public:
    
    bool isStarted() { return isRunning; }
    bool start(unsigned short port);
    void stop();
    
};
