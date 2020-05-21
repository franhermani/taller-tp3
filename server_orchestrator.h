#ifndef SERVER_ORCHESTRATOR_H
#define SERVER_ORCHESTRATOR_H

#include <vector>
#include "server_number_guesser.h"

class ServerOrchestrator {
    std::vector<NumberGuesser> numbers;

public:
    // Constructor
    ServerOrchestrator();

    // Constructor y asignacion por copia deshabilitados
    ServerOrchestrator(const ServerOrchestrator& other) = delete;
    ServerOrchestrator& operator=(const ServerOrchestrator& other) = delete;

    // Lee el archivo de numeros, crea un NumberGuesser para cada uno
    // y lo almacena en el vector 'numbers'
    void parseNumbersFile(const char *path);
};

#endif // SERVER_ORCHESTRATOR_H
