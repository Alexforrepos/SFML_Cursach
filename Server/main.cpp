#include "Server.h"
#include <iostream>

int main() 
{
    const unsigned short port = 50001;
    char role;

    std::cout << "Choose role (s - server, c - client): ";
    std::cin >> role;
    std::cin.ignore(); // Clear input buffer

    if (role == 's') 
    {
        Server server;
        if (!server.start(port)) return 1;

        // Keep main thread alive
        while (true) std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    else if (role == 'c') 
    {
        Client client;
        if (!client.connect("127.0.0.1", port)) return 1;

        // Keep main thread alive
        while (true) std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}