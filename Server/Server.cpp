#include "Server.h"
#include <string>

bool Server::start(unsigned short port) 
{
    if (listener.listen(port) != sf::Socket::Done) 
    {
        std::cerr << "Failed to bind port " << port << std::endl;
        return false;
    }

    std::cout << "Server started on port " << port << std::endl;
    isRunning = true;

    // Accept connection in separate thread
    std::thread acceptThread([this]() 
        {
        if (listener.accept(clientSocket) != sf::Socket::Done)
        {
            std::cerr << "Accept connection failed" << std::endl;
            return;
        }
        std::cout << "Client connected: " << clientSocket.getRemoteAddress() << std::endl;

        // Start communication threads
        std::thread(&Server::clientHandler, this).detach();
        std::thread(&Server::inputHandler, this).detach();
        });
    acceptThread.detach();

    return true;
}

void Server::clientHandler() 
{
    while (isRunning) 
    {
        char buffer[1024];
        std::size_t received;
        if (clientSocket.receive(buffer, sizeof(buffer), received) == sf::Socket::Done) 
        {
            std::string message(buffer, received);
            std::cout << "Client: " << message << std::endl;
        }
    }
}

void Server::inputHandler() 
{
    std::string message;
    while (isRunning) {
        std::getline(std::cin, message);
        if (message == "exit") 
        {
            stop();
            break;
        }
        clientSocket.send(message.c_str(), message.size() + 1);
    }
}

void Server::stop() 
{
    isRunning = false;
    clientSocket.disconnect();
    listener.close();
    std::cout << "Server stopped" << std::endl;
}

// Client implementation
bool Client::connect(const std::string& ip, unsigned short port) 
{
    if (socket.connect(ip, port) != sf::Socket::Done) 
    {
        std::cerr << "Connection failed" << std::endl;
        return false;
    }

    isConnected = true;
    std::cout << "Connected to server" << std::endl;

    std::thread(&Client::receiveHandler, this).detach();
    std::thread(&Client::inputHandler, this).detach();

    return true;
}

void Client::receiveHandler() 
{
    while (isConnected) 
    {
        char buffer[1024];
        std::size_t received;
        if (socket.receive(buffer, sizeof(buffer), received) == sf::Socket::Done) 
        {
            std::string message(buffer, received);
            std::cout << "Server: " << message << std::endl;
        }
    }
}

void Client::inputHandler() 
{
    std::string message;
    while (isConnected) 
    {
        std::getline(std::cin, message);
        if (message == "exit") 
        {
            disconnect();
            break;
        }
        socket.send(message.c_str(), message.size() + 1);
    }
}

void Client::disconnect() 
{
    isConnected = false;
    socket.disconnect();
    std::cout << "Disconnected" << std::endl;
}