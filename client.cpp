#include <iostream>
#include <string.h>
#include <climits>
#include "client.h"
#include "common_defines.h"
#include "common_socket_error.h"

#define RET 0
#define NUM_PARAMS 3
#define FIRST_SIZE 4
#define BUF_MAX_SIZE 256

int main(int argc, char *argv[]) {
    if (argc != NUM_PARAMS) {
        std::cerr << "Error: argumentos inválidos\n";
        return RET;
    }
    const char *host = argv[1], *port = argv[2];
    try {
        Client client(host, port);
        std::string command;
        while (getline(std::cin, command)) {
            if (! client.isValidCommand(command)) {
                std::cout << "Error: comando inválido. Escriba AYUDA "
                             "para obtener ayuda\n";
            } else {
                client.interactWithServer(command);
                if (client.isGameOver()) break;
            }
        }
    } catch(SocketError& e) {
        std::cerr << e.what() << "\n";
    } catch(...) {
        std::cerr << "Error desconocido\n";
    }
    return RET;
}

Client::Client(const char *host, const char *port) :
socket(host, port, false), keepPlaying(true) {}

const bool Client::isValidCommand(const std::string& command) const {
    return (command == HELP || command == SURRENDER || isValidNumber(command));
}

const bool Client::isValidNumber(const std::string& command) const {
    try {
        if (std::stoi(command) > USHRT_MAX) return false;
    } catch(...) {
        return false;
    }
    return true;
}

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

const bool Client::isGameOver() const {
    return (! keepPlaying);
}
