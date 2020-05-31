#include <iostream>
#include <string>
#include <utility>
#include "server.h"
#include "server_file.h"

Server::Server(File& file, const char *host, const char *port) :
numbers_file(file) {
    threadAcceptor = new ThreadAcceptor(host, port, numbers, gameStats);
}

Server::~Server() {
    delete threadAcceptor;
}

void Server::parseNumbersFile() {
    std::string line;
    while (getline(numbers_file.getFile(), line)) {
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
