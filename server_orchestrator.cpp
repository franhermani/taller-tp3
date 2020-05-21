#include <iostream>
#include <string>
#include <utility>
#include "server_orchestrator.h"
#include "common_file.h"

ServerOrchestrator::ServerOrchestrator(File& file) : numbers_file(file) {}

void ServerOrchestrator::parseNumbersFile() {
    std::string line;
    while (numbers_file.readLine(line)) {
        NumberGuesser numberGuesser(std::stoi(line));
        numbers.push_back(std::move(numberGuesser));
    }
    numbers_file.closeFD();
}

void ServerOrchestrator::printGamesPlayedStats() {
    std::cout << "Estadísticas:\n\tGanadores:  <cant>\n\tPerdedores: <cant>\n";
}
