#include <iostream>
#include <exception>
#include "client_defines.h"

#define RET 0
#define NUM_PARAMS 3

const bool isValidCommand(std::string command);

const bool isValidNumber(std::string command);

int main(int argc, char *argv[]) {
    if (argc != NUM_PARAMS) {
        std::cerr << "Error: argumentos inválidos\n";
        return RET;
    }
//    const char *host = argv[1], *port = argv[2];

    std::string command;
    while (getline(std::cin, command)) {
        if (! isValidCommand(command)) {
            std::cout << "Error: comando inválido. Escriba " << HELP
                      << " para obtener ayuda\n";
        } else {
            // TODO: ...
            std::cout << "Comando recibido OK\n";
        }
    }
    return RET;
}

const bool isValidCommand(std::string command) {
    return (command == HELP || command == SURRENDER || isValidNumber(command));
}

const bool isValidNumber(std::string command) {
    try {
        int number = std::stoi(command);
        if (number < MIN_NUM || number > MAX_NUM) return false;
    } catch(std::invalid_argument) {
        return false;
    }
    return true;
}
