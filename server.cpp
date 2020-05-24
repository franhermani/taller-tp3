#include <iostream>
#include <string>
#include <string.h>
#include <utility>
#include <exception>
#include "server.h"
#include "server_defines.h"
#include "server_file.h"
#include "common_socket.h"

#define OK 0
#define ERROR 1
#define NUM_PARAMS 3
#define BYTE_SIZE 1
#define NUMBER_SIZE 2

int main(int argc, char *argv[]) {
    if (argc != NUM_PARAMS) {
        std::cerr << "Error: argumentos inválidos\n";
        return ERROR;
    }
    const char *host = 0, *port = argv[1], *path = argv[2];

    try {
        File file(path);
        Server server(file, host, port);
        server.parseNumbersFile();
        server.startThreadInput();
        server.startThreadAcceptor();
        server.interactWithClients();
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

Server::Server(File& file, const char *host, const char *port) :
numbers_file(file), num_winners(0), num_losers(0) {
    threadInput = new ThreadInput();
    threadAcceptor = new ThreadAcceptor(host, port, clients);
}

Server::~Server() {
    threadInput->join();
    delete threadInput;

    threadAcceptor->join();
    delete threadAcceptor;
}

void Server::parseNumbersFile() {
    std::string line;
    while (numbers_file.readLine(line)) {
        NumberGuesser numberGuesser(std::stoi(line));
        numbers.push_back(std::move(numberGuesser));
    }
    numbers_file.closeFD();
}

void Server::startThreadInput() {
    threadInput->start();
}

void Server::startThreadAcceptor() {
    threadAcceptor->start();
}

// TODO: esta funcion va en el acceptor (creo)
void Server::interactWithClients() {
    char buffer_byte[BYTE_SIZE];
    Socket socket_acceptor(0, "8080");
    socket_acceptor.listenToClients();

    Socket socket_client = socket_acceptor.acceptClients();

    socket_client.receiveBytes(buffer_byte, BYTE_SIZE);
    uint32_t length = protocol.decodeMessageLength(buffer_byte);

    if (length > 0) {
        char buffer_number[NUMBER_SIZE];
        socket_client.receiveBytes(buffer_number, length);
        std::string number_str = protocol.decodeMessageValue(buffer_number);
        processClientNumber(stoi(number_str));
    } else {
        ByteMsg byte_msg = protocol.encodeMessage(buffer_byte);
        socket_client.sendBytes(byte_msg.value, byte_msg.pos + 1);
    }
}

void Server::processClientNumber(const int number) {
    // TODO: ...
}

void Server::printGamesPlayedStats() {
    std::cout << "Estadísticas:\n\tGanadores:  " << num_winners <<
              "\n\tPerdedores: " << num_losers << "\n";
}
