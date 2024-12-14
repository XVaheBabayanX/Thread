#include "MessengerSocket.h"
#include <stdexcept>
#include <iostream>

MessengerSocket::MessengerSocket()
{
#ifdef _WIN32
    WSADATA wsa_data;
    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
    {
        throw std::runtime_error("Failed to initialize Winsock.");
    }
#endif

    socket_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (socket_fd == INVALID_SOCKET)
    {
        throw std::runtime_error("Failed to create socket.");
    }
}

MessengerSocket::~MessengerSocket()
{
    if (socket_fd != INVALID_SOCKET)
    {
#ifdef _WIN32
        closesocket(socket_fd);
        WSACleanup();
#else
        close(socket_fd);
#endif
    }
}

SOCKET MessengerSocket::GetSocket() const
{
    return socket_fd;
}

void MessengerSocket::SendMessage(const std::string& message, const sockaddr_in& dest_address)
{
    if (sendto(socket_fd, message.c_str(), static_cast<int>(message.size()), 0,
        reinterpret_cast<const struct sockaddr*>(&dest_address), sizeof(dest_address)) == SOCKET_ERROR)
    {
        throw std::runtime_error("Failed to send message.");
    }
}

std::string MessengerSocket::ReceiveMessage(sockaddr_in& src_address)
{
    char buffer[1024];
    socklen_t address_length = sizeof(src_address);

    int received_length = recvfrom(socket_fd, buffer, sizeof(buffer) - 1, 0,
        reinterpret_cast<struct sockaddr*>(&src_address), &address_length);

    if (received_length == SOCKET_ERROR)
    {
        throw std::runtime_error("Failed to receive message.");
    }

    buffer[received_length] = '\0'; 
    return std::string(buffer);
}
