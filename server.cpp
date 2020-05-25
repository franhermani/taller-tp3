#include <iostream>
#include <string>
#include <string.h>
#include <utility>
#include <exception>
#include "server.h"
#include "server_defines.h"
#include "server_file.h"

#define OK 0
#define ERROR 1
#define NUM_PARAMS 3

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
        server.startThreadAcceptor();

        std::string command;
        while (getline(std::cin, command)) {
            if (command == EXIT_CHAR) {
                server.stopThreadAcceptor();
                break;
            }
        }
        server.joinThreadAcceptor();
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
numbers_file(file) {
    threadAcceptor = new ThreadAcceptor(host, port, numbers, gameStats);
}

Server::~Server() {
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

void Server::startThreadAcceptor() {
    threadAcceptor->start();
}

void Server::stopThreadAcceptor() {
    threadAcceptor->stop();
}

void Server::joinThreadAcceptor() {
    threadAcceptor->join();
}

void Server::printGamesPlayedStats() {
    std::cout << "Estadísticas:\n\tGanadores:  " << gameStats.getWinners() <<
              "\n\tPerdedores: " << gameStats.getLosers() << "\n";
}
