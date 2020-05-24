#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include "server_file.h"
#include "server_number_guesser.h"
#include "server_protocol.h"
#include "server_thread_acceptor.h"
#include "server_thread_client.h"

class Server {
    File& numbers_file;
    ServerProtocol protocol;
    ThreadAcceptor *threadAcceptor;
    std::vector<NumberGuesser> numbers;
    int num_winners;
    int num_losers;

public:
    // Constructor
    Server(File& file, const char *host, const char *port);

    // Constructor y asignacion por copia deshabilitados
    Server(const Server& other) = delete;
    Server& operator=(const Server& other) = delete;

    // Destructor
    ~Server();

    // Lee el archivo de numeros, crea un NumberGuesser para cada uno
    // y lo almacena en el vector 'numbers'
    void parseNumbersFile();

    // Inicializa el threadAcceptor
    void startThreadAcceptor();

    // Finaliza el threadAcceptor
    void finishThreadAcceptor();

    // Imprime por pantalla las estadisticas de las partidas jugadas
    void printGamesPlayedStats();
};

#endif // SERVER_H
