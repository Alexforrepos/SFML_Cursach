#pragma once
#include <memory>
#include "Engine/MSG.h"
#include "./../Room/Room.h"
#include <vector>
#include <SFML/Network.hpp>
#include <iostream>
#include <thread>
#include <atomic>

#define PORT1 53000
#define PORT2 53200 
#define MAXROOM 10

class Server
{
public:
    enum class Status : uint8_t
    {
        STOPPED, WAIT_FOR_CONNECTION, NOT_READY_HANDLE
    };

    Server::Status getStatus() { return status_; }

    // Добавленные методы
    bool connectClient()
    {
        auto clientSocket = std::make_unique<sf::TcpSocket>();
        if (listener.accept(*clientSocket) == sf::Socket::Done)
        {
            std::cout << "Client connected: " << clientSocket->getRemoteAddress() << std::endl;
            clientSockets.push_back(std::move(clientSocket));
            return true;
        }
        return false;
    }

    bool testConnection(sf::TcpSocket& socket)
    {
        sf::Packet packet;
        packet << "xyi";
        if (socket.send(packet) != sf::Socket::Done)
        {
            std::cerr << "packets proebani\n";
            return false;
        }

        packet.clear();
        if (socket.receive(packet) == sf::Socket::Done)
        {
            std::string response;
            packet >> response;
            return (response == "pizdaaaaa");
        }
        return false;
    }

public:
    static void HandleClient(std::unique_ptr<sf::TcpSocket> socket)
    {
        std::thread([socket = std::move(socket)]() mutable
            {
                Server server;
                if (server.testConnection(*socket))
                {
                    std::cout << "Connection test successful\n";
                }
            }).detach();
    };

private:
    Status status_;
    sf::TcpListener listener;
    std::vector<std::unique_ptr<sf::TcpSocket>> clientSockets;

public:
    Server() {}

    ~Server()
    {
        stop();
    }

    void start(const unsigned& port = PORT1)
    {
        if (listener.listen(port) == sf::Socket::Done)
        {
            status_ = Status::WAIT_FOR_CONNECTION;
            std::cout << "Server started on port " << port << std::endl;
        }
    }

    void stop()
    {
        listener.close();
        clientSockets.clear();
    }

    void HandleAClient()
    {
        if (!clientSockets.empty())
        {
            auto socket = std::move(clientSockets.back());
            clientSockets.pop_back();
            HandleClient(std::move(socket));
        }
    }
};