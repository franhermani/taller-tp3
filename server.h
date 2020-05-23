#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include "server_number_guesser.h"
#include "common_file.h"
#include "server_protocol.h"

class Server {
    File& numbers_file;
    std::vector<NumberGuesser> numbers;
    ServerProtocol protocol;
    int num_winners;
    int num_losers;

public:
    // Constructor
    explicit Server(File& file);

    // Constructor y asignacion por copia deshabilitados
    Server(const Server& other) = delete;
    Server& operator=(const Server& other) = delete;

    // Lee el archivo de numeros, crea un NumberGuesser para cada uno
    // y lo almacena en el vector 'numbers'
    void parseNumbersFile();

    // Interactua con los clientes (envia y recibe mensajes)
    void interactWithClients();

    // Recibe el numero enviado por el cliente
    void processClientNumber(const int number);

    // Imprime por pantalla las estadisticas de las partidas jugadas
    void printGamesPlayedStats();
};

#endif // SERVER_H
