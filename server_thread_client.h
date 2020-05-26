#ifndef THREAD_CLIENT_H
#define THREAD_CLIENT_H

#include <atomic>
#include <string>
#include "server_thread.h"
#include "common_socket.h"
#include "server_protocol.h"
#include "server_number_guesser.h"
#include "server_game_stats.h"

class ThreadClient : public Thread {
    Socket socket;
    ServerProtocol protocol;
    NumberGuesser& numberGuesser;
    GameStats& gameStats;
    std::atomic<bool> keep_talking;
    std::atomic<bool> is_running;
    std::atomic<bool> is_finished;
    int num_tries;

    // Interactua con los clientes (envia y recibe mensajes)
    void interactWithClient();

    // Recibe un mensaje del cliente
    // Devuelve la respuesta a enviarle
    const std::string receiveMessage();

    // Envia un mensaje al cliente
    void sendMessage(const std::string& message);

    // Recibe el numero enviado por el cliente
    const int receiveNumber(size_t length);

    // Procesa el numero enviado por el cliente
    // Devuelve el mensaje de respuesta
    const std::string processNumber(const int number);

    // Devuelve la respuesta al numero enviado por el cliente
    const std::string writeNumberAnswer(const int number);

public:
    // Constructor
    ThreadClient(Socket socket, NumberGuesser& number_guesser,
            GameStats& game_stats);

    // Constructor y asignacion por copia deshabilitados
    ThreadClient(const ThreadClient&) = delete;
    ThreadClient& operator=(const ThreadClient&) = delete;

    // Llama a interactWithClient hasta que finalice la partida
    virtual void run() override;

    // Setea la variable booleana 'keep_talking' en false
    virtual void stop() override;

    // Devuelve true si el thread no esta corriendo o
    // false en caso contrario
    virtual const bool isDead() override;
};

#endif // THREAD_CLIENT_H
