#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include "server_orchestrator.h"

ServerOrchestrator::ServerOrchestrator() {}

void ServerOrchestrator::parseNumbersFile(const char *path) {
    std::ifstream numbers_file;
    numbers_file.open(path, std::ifstream::in);
    if (! numbers_file.good())
        throw std::runtime_error("Error al abrir el archivo de números\n");

    std::string line;
    while (getline(numbers_file, line)) {
        NumberGuesser numberGuesser(std::stoi(line));
        numbers.push_back(std::move(numberGuesser));
    }
}
