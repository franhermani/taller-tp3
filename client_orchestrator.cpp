#include <iostream>
#include <string>
#include <exception>
#include "client_orchestrator.h"
#include "common_defines.h"

ClientOrchestrator::ClientOrchestrator() {}

const bool ClientOrchestrator::isValidCommand(std::string command) {
    return (command == HELP || command == SURRENDER || isValidNumber(command));
}

const bool ClientOrchestrator::isValidNumber(std::string command) {
    try {
        int number = std::stoi(command);
        if (number < MIN_NUM || number > MAX_NUM) return false;
    } catch(std::invalid_argument) {
        return false;
    }
    return true;
}
