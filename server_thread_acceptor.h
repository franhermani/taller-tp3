#ifndef THREAD_ACCEPTOR_H
#define THREAD_ACCEPTOR_H

#include <vector>
#include <atomic>
#include "server_thread.h"
#include "common_socket.h"
#include "server_number_guesser.h"
#include "server_thread_client.h"
#include "server_game_stats.h"

class ThreadAcceptor : public Thread {
    Socket socket;
    std::vector<NumberGuesser>& numbers;
    std::vector<ThreadClient*> clients;
    GameStats& gameStats;
    std::atomic<bool> keep_talking;
    std::atomic<bool> is_running;
    int actual_number_pos;

    // Crea el thread del cliente
    void createThreadClient();

    // Inicializa el thread del cliente
    void startThreadClient();

    // Recorre el vector de clientes y elimina aquellos que ya finalizaron
    // Libera la memoria reservada
    void cleanDeadClients();

    // Recorre el vector de clientes y espera a que finalicen
    // Libera la memoria reservada
    void joinClients();

    // Actualiza la posicion en el vector 'numbers' del numero actual
    void updateNumberPos();

public:
    // Constructor
    ThreadAcceptor(const char *host, const char *port,
            std::vector<NumberGuesser>& numbers, GameStats& game_stats);

    // Constructor y asignacion por copia deshabilitados
    ThreadAcceptor(const ThreadAcceptor&) = delete;
    ThreadAcceptor& operator=(const ThreadAcceptor&) = delete;

    // Acepta clientes, crea sus threads, los almacena en el vector 'clients'
    // y los pone a correr
    virtual void run() override;

    // Setea la variable booleana 'keep_talking' en false
    virtual void stop() override;

    // Devuelve true si el thread no esta corriendo o false en caso contrario
    virtual const bool isDead() override;
};

#endif // THREAD_ACCEPTOR_H
