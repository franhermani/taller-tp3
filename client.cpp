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
            ByteMsg byte_msg = orchestrator.encodeMessage(command);
            for (int i=0; i < byte_msg.pos; i++)
                printf("%02X ", (unsigned) (unsigned char) byte_msg.value[i]);
            printf("\n");
            // TODO: enviar comando al server
        }
    }
    return RET;
}
