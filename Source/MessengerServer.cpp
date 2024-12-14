#include "MessengerServer.h"
#include <iostream>
#include <cstring>
#include <stdexcept>

MessengerServer::MessengerServer(unsigned short port)
{
    address_length = sizeof(server_address);
    memset(&server_address, 0, address_length);

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(port);

    if (bind(socket.GetSocket(), reinterpret_cast<struct sockaddr*>(&server_address), address_length) == -1)
    {
        throw std::runtime_error("Failed to bind the socket.");
    }
    std::cout << "Server started on port " << port << std::endl;
}

void MessengerServer::StartListening()
{
    std::cout << "Waiting for messages..." << std::endl;
}

std::string MessengerServer::ReceiveMessage(sockaddr_in& client_address)
{
    return socket.ReceiveMessage(client_address);
}

void MessengerServer::SendMessage(const std::string& message, const sockaddr_in& client_address)
{
    socket.SendMessage(message, client_address);
}
