#ifndef THREAD_CLIENT_H
#define THREAD_CLIENT_H

#include <atomic>
#include "server_thread.h"
#include "common_socket.h"
#include "server_protocol.h"
#include "server_number_guesser.h"

class ThreadClient : public Thread {
    Socket socket;
    ServerProtocol protocol;
    NumberGuesser& numberGuesser;
    std::atomic<bool> keep_talking;
    std::atomic<bool> is_running;

public:
    // Constructor
    ThreadClient(Socket socket, NumberGuesser& number_guesser);

    // Constructor y asignacion por copia deshabilitados
    ThreadClient(const ThreadClient&) = delete;
    ThreadClient& operator=(const ThreadClient&) = delete;

    // Interactua con los clientes (envia y recibe mensajes)
    void interactWithClient();

    // Recibe el numero enviado por el cliente
    void processClientNumber(const int number);

    // TODO: ...
    virtual void run() override;

    // Setea la variable booleana 'keep_talking' en false
    virtual void stop() override;

    // Devuelve true si el thread no esta corriendo o
    // false en caso contrario
    virtual const bool isDead() override;
};

#endif // THREAD_CLIENT_H
