#include <iostream>
#include "client_orchestrator.h"

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
            // TODO: enviar comando al server
            std::cout << "Comando recibido OK\n";
        }
    }
    return RET;
}
