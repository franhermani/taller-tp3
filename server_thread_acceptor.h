#ifndef THREAD_ACCEPTOR_H
#define THREAD_ACCEPTOR_H

#include <vector>
#include <atomic>
#include "server_thread.h"
#include "common_socket.h"
#include "server_thread_client.h"
#include "server_number_guesser.h"
#include "server_game_stats.h"

class ThreadAcceptor : public Thread {
    Socket socket;
    std::vector<NumberGuesser>& numbers;
    GameStats& gameStats;
    std::vector<ThreadClient*> clients;
    std::atomic<bool> keep_talking;
    std::atomic<bool> is_running;

    // Crea el thread del cliente
    void createThreadClient();

    // Recorre el vector de clientes y limpia aquellos que ya finalizaron
    void cleanDeadClients();

    // Recorre el vector de clientes y espera a que finalicen
    // Libera la memoria reservada
    void joinClients();

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

    // Devuelve true si el thread no esta corriendo o
    // false en caso contrario
    virtual const bool isDead() override;
};

#endif // THREAD_ACCEPTOR_H
