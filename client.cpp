#include <iostream>
#include <string.h>
#include <exception>
#include "client.h"
#include "common_defines.h"
#include "common_socket.h"

#define RET 0
#define NUM_PARAMS 3

int main(int argc, char *argv[]) {
    if (argc != NUM_PARAMS) {
        std::cerr << "Error: argumentos inválidos\n";
        return RET;
    }
//    const char *host = argv[1], *port = argv[2];

    Client client;

    std::string command;
    while (getline(std::cin, command)) {
        if (! client.isValidCommand(command)) {
            std::cout << "Error: comando inválido. Escriba AYUDA "
                         "para obtener ayuda\n";
        } else {
            client.interactWithServer(command);
        }
    }
    return RET;
}

Client::Client() {}

const bool Client::isValidCommand(const std::string command)
const {
    return (command == HELP || command == SURRENDER || isValidNumber(command));
}

const bool Client::isValidNumber(const std::string command)
const {
    try {
        int number = std::stoi(command);
        if (number < MIN_NUM || number > MAX_NUM) return false;
    } catch(...) {
        return false;
    }
    return true;
}

void Client::interactWithServer(const std::string command) {
    ByteMsg byte_msg = protocol.encodeMessage(command);
    for (int i=0; i < byte_msg.pos; i++)
        printf("%02X ", (unsigned) (unsigned char) byte_msg.value[i]);
    printf("\n");
    // TODO: enviar comando al server
}
