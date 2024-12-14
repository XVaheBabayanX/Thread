#include "MessengerClient.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    std::string server_ip = "127.0.0.1";
    unsigned short server_port = 8888;

    if (argc == 2)
    {
        server_port = static_cast<unsigned short>(std::stoi(argv[1]));
    }
    else if (argc == 3)
    {
        server_ip = argv[1];
        server_port = static_cast<unsigned short>(std::stoi(argv[2]));
    }

    try
    {
        MessengerClient client(server_ip, server_port);

        while (true)
        {
            std::cout << "Enter message: ";
            std::string message;
            std::getline(std::cin, message);

            client.SendMessage(message);

            std::string response = client.ReceiveMessage();
            std::cout << "Server: " << response << std::endl;
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}