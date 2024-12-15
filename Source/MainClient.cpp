#include "MessengerClient.h"
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>

std::mutex mtx;
std::condition_variable cv;
std::atomic<bool> message_sent(false); 
std::atomic<bool> running(true);       

void message_sender(MessengerClient& client) {
    while (running) {
        std::string message;
        {
            std::lock_guard<std::mutex> lock(mtx);
            std::cout << "Enter message: ";
            std::getline(std::cin, message);
        }

        if (message == "/exit") {
            running = false; 
            cv.notify_one();
            break;
        }

        {
            std::lock_guard<std::mutex> lock(mtx);
            client.SendMessage(message);
            message_sent = true; 
        }

        cv.notify_one(); 
    }
}

void message_receiver(MessengerClient& client) {
    while (running) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return message_sent || !running; }); 

        if (!running) {
            break;
        }

        std::string response = client.ReceiveMessage(); 
        std::cout << "Server: " << response << std::endl;

        message_sent = false; 
    }
}

int main(int argc, char* argv[]) {
    std::string server_ip = "127.0.0.1";
    unsigned short server_port = 8888;

    if (argc == 2) {
        server_port = static_cast<unsigned short>(std::stoi(argv[1]));
    }
    else if (argc == 3) {
        server_ip = argv[1];
        server_port = static_cast<unsigned short>(std::stoi(argv[2]));
    }

    try {
        MessengerClient client(server_ip, server_port);

        std::thread sender_thread(message_sender, std::ref(client));
        std::thread receiver_thread(message_receiver, std::ref(client));

        sender_thread.join();
        receiver_thread.join();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}