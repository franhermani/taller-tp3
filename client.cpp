#include <iostream>
#include <string>
#include <climits>
#include "client.h"
#include "common_defines.h"
#include "common_socket_error.h"

#define FIRST_SIZE 4
#define BUF_MAX_SIZE 256

Client::Client(const char *host, const char *port) :
socket(host, port, false), keepPlaying(true) {}

void Client::interactWithServer(const std::string& command) {
    sendMessage(command);
    std::string response = receiveMessage();
    if (response == WIN_MSG || response == LOSE_MSG) keepPlaying = false;
}

void Client::sendMessage(const std::string& message) {
    ByteMsg byte_msg = protocol.encodeMessage(message.c_str());
    socket.sendBytes(byte_msg.value, byte_msg.pos);
}

const std::string Client::receiveMessage() {
    char buffer_length[FIRST_SIZE];
    char buffer_value[BUF_MAX_SIZE];

    socket.receiveBytes(buffer_length, FIRST_SIZE);
    uint32_t length = protocol.decodeMessageLength(buffer_length);
    socket.receiveBytes(buffer_value, length);
    buffer_value[length] = '\0';

    std::string response = protocol.decodeMessageValue(buffer_value);
    std::cout << response << "\n";

    return response;
}

const bool Client::isValidCommand(const std::string& command) const {
    return (command == HELP || command == SURRENDER || isValidNumber(command));
}

const bool Client::isValidNumber(const std::string& command) const {
    try {
        int number = std::stoi(command);
        if (number < 0 || number > USHRT_MAX) return false;
    } catch(...) {
        return false;
    }
    return true;
}

const bool Client::isGameOver() const {
    return (! keepPlaying);
}
