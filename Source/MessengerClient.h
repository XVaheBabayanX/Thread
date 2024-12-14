#pragma once
#include "MessengerSocket.h"
#include <string>
#include <iostream>
#include <stdexcept>
#include <cstring>

class MessengerClient
{
private:
    MessengerSocket socket;
    sockaddr_in server_address;
    socklen_t address_length;

public:
    MessengerClient(const std::string& server_ip, unsigned short server_port);

    void SendMessage(const std::string& message);
    std::string ReceiveMessage();
};