#ifndef SERVER_ORCHESTRATOR_H
#define SERVER_ORCHESTRATOR_H

#include <vector>
#include "server_number_guesser.h"
#include "common_file.h"

class ServerOrchestrator {
    File& numbers_file;
    std::vector<NumberGuesser> numbers;

public:
    // Constructor
    explicit ServerOrchestrator(File& file);

    // Constructor y asignacion por copia deshabilitados
    ServerOrchestrator(const ServerOrchestrator& other) = delete;
    ServerOrchestrator& operator=(const ServerOrchestrator& other) = delete;

    // Lee el archivo de numeros, crea un NumberGuesser para cada uno
    // y lo almacena en el vector 'numbers'
    void parseNumbersFile();

    // Imprime por pantalla las estadisticas de las partidas jugadas
    void printGamesPlayedStats();
};

#endif // SERVER_ORCHESTRATOR_H
