#include <iostream>
#include <string>
#include <exception>
#include "client_orchestrator.h"
#include "common_defines.h"

ClientOrchestrator::ClientOrchestrator() {}

const bool ClientOrchestrator::isValidCommand(const std::string command)
const {
    return (command == HELP || command == SURRENDER || isValidNumber(command));
}

const bool ClientOrchestrator::isValidNumber(const std::string command)
const {
    try {
        int number = std::stoi(command);
        if (number < MIN_NUM || number > MAX_NUM) return false;
    } catch(...) {
        return false;
    }
    return true;
}

ByteMsg ClientOrchestrator::encodeCommand(const std::string command) {
    return protocol.encodeMessage(command);
}
