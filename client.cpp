#include <iostream>
#include <string.h>
#include "client_orchestrator.h"
#include "common_socket.h"

#define RET 0
#define NUM_PARAMS 3

int main(int argc, char *argv[]) {
    if (argc != NUM_PARAMS) {
        std::cerr << "Error: argumentos inválidos\n";
        return RET;
    }
//    const char *host = argv[1], *port = argv[2];

    ClientOrchestrator orchestrator;

    std::string command;
    while (getline(std::cin, command)) {
        if (! orchestrator.isValidCommand(command)) {
            std::cout << "Error: comando inválido. Escriba AYUDA "
                         "para obtener ayuda\n";
        } else {
            ByteMsg byte_msg = orchestrator.applyProtocol(command);
            std::cout << byte_msg.value << "\n";
            // TODO: enviar comando al server
        }
    }
    return RET;
}
