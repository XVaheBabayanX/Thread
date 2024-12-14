#include "MessengerClient.h"

MessengerClient::MessengerClient(const std::string& server_ip, unsigned short server_port)
{
    address_length = sizeof(server_address);
    memset(&server_address, 0, address_length);

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(server_port);

    if (inet_pton(AF_INET, server_ip.c_str(), &server_address.sin_addr) <= 0)
    {
        throw std::runtime_error("Invalid server IP address.");
    }
}

void MessengerClient::SendMessage(const std::string& message)
{
    socket.SendMessage(message, server_address);
}

std::string MessengerClient::ReceiveMessage()
{
    sockaddr_in sender_address;
    return socket.ReceiveMessage(sender_address);
}
