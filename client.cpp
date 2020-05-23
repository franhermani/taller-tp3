#include <iostream>
#include <string.h>
#include "client.h"
#include "common_defines.h"
#include "common_socket_error.h"

#define RET 0
#define NUM_PARAMS 3
#define BUF_MAX_SIZE 256
#define FIRST_SIZE 4

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
            }
        }
    } catch(SocketError& e) {
        std::cerr << e.what() << "\n";
    } catch(...) {
        std::cerr << "Error desconocido\n";
    }
    return RET;
}

Client::Client(const char *host, const char *port) : socket(host, port) {}

const bool Client::isValidCommand(const std::string& command)
const {
    return (command == HELP || command == SURRENDER || isValidNumber(command));
}

const bool Client::isValidNumber(const std::string& command)
const {
    try {
        int number = std::stoi(command);
        if (number < MIN_NUM || number > MAX_NUM) return false;
    } catch(...) {
        return false;
    }
    return true;
}

void Client::interactWithServer(const std::string& command) {
    ByteMsg byte_msg = protocol.encodeMessage(command);
    sendMessage(byte_msg);
    receiveMessage();
}

void Client::sendMessage(ByteMsg& byte_msg) {
    socket.sendBytes(byte_msg.value, (size_t) byte_msg.pos);
}

void Client::receiveMessage() {
    char buffer_length[FIRST_SIZE + 1];
    char buffer_value[BUF_MAX_SIZE];

    socket.receiveBytes(buffer_length, FIRST_SIZE);
    buffer_length[FIRST_SIZE] = '\0';

    uint32_t length = protocol.decodeMessageLength(buffer_length);
    socket.receiveBytes(buffer_value, (size_t) length);
    buffer_value[length] = '\0';

    std::cout << buffer_value << "\n";
}
