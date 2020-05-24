#ifndef THREAD_CLIENT_H
#define THREAD_CLIENT_H

#include "server_thread.h"
#include "common_socket.h"

class ThreadClient : public Thread {
    Socket socket;

public:
    // Constructor
    explicit ThreadClient(Socket socket);

    // Constructor y asignacion por copia deshabilitados
    ThreadClient(const ThreadClient&) = delete;
    ThreadClient& operator=(const ThreadClient&) = delete;

    // Interactua con los clientes (envia y recibe mensajes)
//    void interactWithClients();

    // Recibe el numero enviado por el cliente
//    void processClientNumber(const int number);

    virtual void run() override;
};

#endif // THREAD_CLIENT_H
