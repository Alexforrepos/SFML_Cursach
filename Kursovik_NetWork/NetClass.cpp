#include "NetClass.h"
#include <iostream>
#include <atomic>
#include <thread>


#pragma region Host


void NetClass::Host::start(unsigned port) {
    if (client.listen(port) != sf::Socket::Done) {
        std::cerr << "Failed to start server on port " << port << std::endl;
        return;
    }
    std::cout << "Server started on port " << port << std::endl;

    // ��������� ����������� �������
    if (client.accept(clientSocket) != sf::Socket::Done) {
        std::cerr << "Failed to accept client connection" << std::endl;
        return;
    }
    std::cout << "Client connected" << std::endl;

    // ��������� ����� ��� ��������� �������� ���������
    std::thread(&Host::HandleClient, this).detach();
}

void NetClass::Host::HandleClient() {
    while (true) {
        sf::Packet packet;
        if (NetClass::get().host.clientSocket.receive(packet) == sf::Socket::Done) 
        {
            // ��������� ��������� ������
            uint8_t msgType;
            packet >> msgType; // ������ ��� ���������
            switch (static_cast<MSG_TYPE>(msgType)) {
                case MSG_TYPE::MSG_TYPE_MOVE: {
                    MSG_TYPE_MOVE moveMsg({0,0},VOID_ID);
                    moveMsg.open(packet);
                    std::cout << "Received MOVE message: (" << moveMsg.dir.x << ", " << moveMsg.dir.y  << ", id:" << moveMsg.id << ")" << std::endl;
                    break;
                }
                // ��������� ������ ����� ���������
                default:
                    std::cerr << "Unknown message type received" << std::endl;
                    break;
            }
        } 
        else 
        {
            // ���� ���������� ���������, ������� �� �����
            std::cerr << "Client disconnected" << std::endl;
            NetClass::get().status = NetClass::Status::NOTISRUN;
            break;
        }
    }
}

void NetClass::Host::send(MSG* msg) {
    sf::Packet packet;
    msg->pack(packet);
    if (clientSocket.send(packet) != sf::Socket::Done) {
        std::cerr << "Failed to send message from server" << std::endl;
    }
}

void NetClass::Host::stop() 
{
    clientSocket.disconnect();
    client.close();
    std::cout << "Server stopped" << std::endl;
}

#pragma endregion

void NetClass::Client::start(sf::IpAddress ip, unsigned port) 
{
    while (true) {
        if (hostSocket.connect(ip, port) == sf::Socket::Done) {
            std::cout << "Connected to server at " << ip.toString() << ":" << port << std::endl;
            break;
        }
        else {
            std::cerr << "Failed to connect to server, retrying in 5 seconds..." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(5));
        }
    }
    std::thread(&Client::HandeHost, this).detach();
}

void NetClass::Client::HandeHost() {
    while (true) {
        sf::Packet packet;
        if (NetClass::get().client.hostSocket.receive(packet) == sf::Socket::Done) {
            // ��������� ��������� ������
            std::cout << "Received packet on client" << std::endl;
            // ����� ����� �������� ������ ��� ��������� ������
        }
        else {
            // ���� ���������� ���������, ������� �� �����
            std::cerr << "Disconnected from server" << std::endl;
            break;
        }
    }
}

void NetClass::Client::send(MSG* msg) {
    sf::Packet packet;
    msg->pack(packet);
    if (hostSocket.send(packet) != sf::Socket::Done) {
        std::cerr << "Failed to send message from client" << std::endl;
    }
}

void NetClass::Client::stop() {
    hostSocket.disconnect();
    std::cout << "Disconnected from server" << std::endl;
}

void NetClass::startClient() {
    if (status == Status::NOTISRUN) {
        status = Status::ISCLINET;
        client.start("127.0.0.1", 53000); // ������ IP � �����
    }
}

void NetClass::stopClient() {
    if (status == Status::ISCLINET) {
        client.stop();
        status = Status::NOTISRUN;
    }
}

void NetClass::send(MSG* msg) {
    if (status == Status::ISHOST) {
        host.send(msg);
    }
    else if (status == Status::ISCLINET) {
        client.send(msg);
    }
}

void NetClass::startHost() {
    if (status == Status::NOTISRUN) {
        status = Status::ISHOST;
        host.start(53000); // ������ �����
    }
}

void NetClass::stopHost() {
    if (status == Status::ISHOST) {
        host.stop();
        status = Status::NOTISRUN;
    }
}

NetClass::Status NetClass::getStatus() {
    return status;
}