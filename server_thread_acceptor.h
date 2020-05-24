#ifndef THREAD_ACCEPTOR_H
#define THREAD_ACCEPTOR_H

#include <vector>
#include "server_thread.h"
#include "common_socket.h"
#include "server_thread_client.h"

class ThreadAcceptor : public Thread {
    Socket socket;
    std::vector<ThreadClient*> clients;

public:
    // Constructor
    ThreadAcceptor(const char *host, const char *port);

    // Constructor y asignacion por copia deshabilitados
    ThreadAcceptor(const ThreadAcceptor&) = delete;
    ThreadAcceptor& operator=(const ThreadAcceptor&) = delete;

    // Acepta clientes, crea sus threads, los almacena en el vector 'clients'
    // y los pone a correr
    virtual void run() override;
};

#endif // THREAD_ACCEPTOR_H
