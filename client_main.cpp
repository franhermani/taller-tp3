#include <iostream>
#include <string>
#include "client.h"
#include "common_socket_error.h"

#define RET 0
#define NUM_PARAMS 3

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
