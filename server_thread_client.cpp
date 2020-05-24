#include <utility>
#include "server_thread_client.h"

ThreadClient::ThreadClient(Socket socket) : socket(std::move(socket)),
keep_talking(true), is_running(true) {}

void ThreadClient::run() {
    while (keep_talking) {
        // TODO: ...
    }
    is_running = false;
}

void ThreadClient::stop() {
    keep_talking = false;
}

const bool ThreadClient::isDead() {
    return (! is_running);
}

/*
void Server::interactWithClients() {
    char buffer_byte[BYTE_SIZE];

    socket_client.receiveBytes(buffer_byte, BYTE_SIZE);
    uint32_t length = protocol.decodeMessageLength(buffer_byte);

    if (length > 0) {
        char buffer_number[NUMBER_SIZE];
        socket_client.receiveBytes(buffer_number, length);
        std::string number_str = protocol.decodeMessageValue(buffer_number);
        processClientNumber(stoi(number_str));
    } else {
        ByteMsg byte_msg = protocol.encodeMessage(buffer_byte);
        socket_client.sendBytes(byte_msg.value, byte_msg.pos + 1);
    }
}

void Server::processClientNumber(const int number) {
    // TODO: ...
}
*/
