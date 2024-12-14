#include "MessengerServer.h"
#include <iostream>
#include <string>
#include <cstring>

int main(int argc, char* argv[])
{
    unsigned short port = 8888;

    if (argc == 2)
    {
        port = static_cast<unsigned short>(std::stoi(argv[1]));
    }

    try
    {
        MessengerServer server(port);
        server.StartListening();

        while (true)
        {
            sockaddr_in client_address;
            std::string message = server.ReceiveMessage(client_address);

            char client_ip[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &client_address.sin_addr, client_ip, INET_ADDRSTRLEN);

            std::cout << "Received from " << client_ip
                << ":" << ntohs(client_address.sin_port) << " - " << message << std::endl;

            std::cout << "Enter response: ";
            std::string response;
            std::getline(std::cin, response);

            server.SendMessage(response, client_address);
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
