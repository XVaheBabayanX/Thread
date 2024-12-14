#pragma once

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#define SOCKET int
#define INVALID_SOCKET (-1)
#define SOCKET_ERROR (-1)
#endif

#include <string>

class MessengerSocket
{
private:
    SOCKET socket_fd;

public:
    MessengerSocket();
    ~MessengerSocket();

    SOCKET GetSocket() const;
    void SendMessage(const std::string& message, const sockaddr_in& dest_address);
    std::string ReceiveMessage(sockaddr_in& src_address);
};
