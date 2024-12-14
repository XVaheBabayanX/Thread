#pragma once
#include "MessengerSocket.h"
#include <string>
#include <stdexcept>

class MessengerServer
{
private:
    MessengerSocket socket;
    sockaddr_in server_address;
    socklen_t address_length;

public:
    MessengerServer(unsigned short port = 8888);

    void StartListening();
    std::string ReceiveMessage(sockaddr_in& client_address);
    void SendMessage(const std::string& message, const sockaddr_in& client_address);
};