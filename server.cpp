#include <iostream>
#include <string>
#include <string.h>
#include <utility>
#include <exception>
#include "server.h"
#include "server_defines.h"
#include "common_file.h"
#include "common_socket.h"

#define OK 0
#define ERROR 1
#define NUM_PARAMS 3
#define FIRST_SIZE 1

int main(int argc, char *argv[]) {
    if (argc != NUM_PARAMS) {
        std::cerr << "Error: argumentos inválidos\n";
        return ERROR;
    }
//    const char *host = 0, *port = argv[1];
    const char *path = argv[2];

    try {
        File file(path);
        Server server(file);
        server.parseNumbersFile();

//        std::string command;
//        while (getline(std::cin, command)) {
//            if (command == EXIT_CHAR) {
                // TODO: esperamos a que terminen todos los clientes
//                break;
//            }
            server.interactWithClients();
//        }
        server.printGamesPlayedStats();
    } catch (const std::exception &e) {
        std::cerr << e.what();
        return ERROR;
    } catch (...) {
        std::cerr << "Error desconocido\n";
        return ERROR;
    }
    return OK;
}

Server::Server(File& file) : numbers_file(file),
num_winners(0), num_losers(0) {}

void Server::parseNumbersFile() {
    std::string line;
    while (numbers_file.readLine(line)) {
        NumberGuesser numberGuesser(std::stoi(line));
        numbers.push_back(std::move(numberGuesser));
    }
    numbers_file.closeFD();
}

void Server::interactWithClients() {
    // TODO: ...
    char buffer1[FIRST_SIZE];
    char buffer2[2];
    Socket socket_acceptor(0, "8080");
    socket_acceptor.listenToClients();

    Socket socket_client = socket_acceptor.acceptClients();

    socket_client.receiveBytes(buffer1, FIRST_SIZE);
    uint32_t length = protocol.decodeMessageLength(buffer1);

    if (length > 0) {
        socket_client.receiveBytes(buffer2, length);
    }
    ByteMsg byte_msg = protocol.encodeMessage(buffer1);
    socket_client.sendBytes(byte_msg.value, byte_msg.pos + 1);
}

void Server::printGamesPlayedStats() {
    std::cout << "Estadísticas:\n\tGanadores:  " << num_winners <<
              "\n\tPerdedores: " << num_losers << "\n";
}
