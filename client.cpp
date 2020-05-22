#include <iostream>
#include <string.h>
#include "client_orchestrator.h"
#include "common_socket.h"

#define RET 0
#define NUM_PARAMS 3

/*
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
*/

int main(int argc, char *argv[]) {
    const char *buffer_send = "Hola mundo!\n";
    char buffer_receive[12];

    Socket socket("localhost", "8080");

    socket.sendBytes(buffer_send, strlen(buffer_send));
    socket.receiveBytes(buffer_receive, 12);

    std::cout << buffer_receive << "\n";

    return RET;
}
