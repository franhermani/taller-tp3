#include <iostream>
#include <string.h>
#include <exception>
#include "server_defines.h"
#include "server_orchestrator.h"
#include "common_file.h"
#include "common_socket.h"

#define OK 0
#define ERROR 1
#define NUM_PARAMS 3

/*
int main(int argc, char *argv[]) {
    if (argc != NUM_PARAMS) {
        std::cerr << "Error: argumentos inválidos\n";
        return ERROR;
    }
//    const char *host = 0, *port = argv[1];
    const char *path = argv[2];

    try {
        File file(path);
        ServerOrchestrator orchestrator(file);
        orchestrator.parseNumbersFile();

        std::string command;
        while (getline(std::cin, command)) {
            if (command == EXIT_CHAR) break;
            // TODO: recibir conexiones de clientes
        }
        orchestrator.printGamesPlayedStats();
    } catch (const std::exception &e) {
        std::cerr << e.what();
        return ERROR;
    } catch (...) {
        std::cerr << "Error desconocido\n";
        return ERROR;
    }
    return OK;
}
*/

int main(int argc, char *argv[]) {
    const char *buffer_send = "Chau mundo!\n";
    char buffer_receive[12];

    Socket socket_acceptor(0, "8080");
    socket_acceptor.listenToClients();

    Socket socket_client = socket_acceptor.acceptClients();
    socket_client.receiveBytes(buffer_receive, 12);
    socket_client.sendBytes(buffer_send, strlen(buffer_send));

    std::cout << buffer_receive << "\n";

    return OK;
}
