#include "server_proxy.h"

#define BYTE_SIZE 1
#define NUMBER_SIZE 2

void ServerProxy::interactWithClient() {}

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