#ifndef CLIENT_ORCHESTRATOR_H
#define CLIENT_ORCHESTRATOR_H

#include <string>

class ClientOrchestrator {
    // Determina si un numero recibido por stdin es valido o no
    const bool isValidNumber(std::string command);

public:
    // Constructor
    ClientOrchestrator();

    // Constructor y asignacion por copia deshabilitados
    ClientOrchestrator(const ClientOrchestrator& other) = delete;
    ClientOrchestrator& operator=(const ClientOrchestrator& other) = delete;

    // Determina si un comando recibido por stdin es valido o no
    const bool isValidCommand(std::string command);
};

#endif // CLIENT_ORCHESTRATOR_H
