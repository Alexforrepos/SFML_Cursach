#pragma once
#include "Engine/MSG.h"
#include <thread>
#include <mutex>
#include <string>
#include <SFML/Network.hpp>

class Client
{
    sf::TcpSocket sendSocket;
    sf::TcpSocket listenSocket;

    std::thread listenerThread;
    std::mutex socketMutex;

    enum Status
    {
        isconserv, isconroom, sleep
    };

    Status st;

    void HandleListenSocket()
    {
        sf::Packet p;
        while (true)
        {
            sf::Socket::Status status = listenSocket.receive(p);
            if (status != sf::Socket::Done)
                break;

            const char* data = static_cast<const char*>(p.getData());
            std::cout << std::string(data, p.getDataSize()) << std::endl;
            p.clear();
        }
    }

public:
    Client() : st(sleep) {}

    ~Client()
    {
        disconnect();
        if (listenerThread.joinable())
            listenerThread.join();
    }

    bool connectToServer(sf::IpAddress ServerIp, uint16_t port, int maxRetries = 3)
    {
        for (int attempt = 0; attempt < maxRetries; ++attempt)
        {
            if (sendSocket.connect(ServerIp, port) == sf::Socket::Done)
            {
                listenerThread = std::thread(&Client::HandleListenSocket, this);
                return true;
            }
            port++;
        }
        throw std::runtime_error("Failed to connect after multiple attempts");
    }

    void connectToRoom(sf::IpAddress ServerIp, uint16_t port)
    {
        std::lock_guard<std::mutex> lock(socketMutex);
        if (sendSocket.connect(ServerIp, port) != sf::Socket::Done)
        {
            throw std::runtime_error("Connection to room failed");
        }
        st = isconroom;
    }


    void disconnect()
    {
        std::lock_guard<std::mutex> lock(socketMutex);
        sendSocket.disconnect();
        listenSocket.disconnect();
        st = sleep;
    }

    void sendMsg(Engine::MSG* msg)
    {
        if (st == sleep)
            throw std::runtime_error("Client is inactive");

        std::lock_guard<std::mutex> lock(socketMutex);
        auto byteData = msg->serializeToStream();
        sf::Packet p;
        p.append(byteData.data(), byteData.size());

        if (sendSocket.send(p) != sf::Socket::Done)
        {
            throw std::runtime_error("Failed to send message");
        }
    }
};