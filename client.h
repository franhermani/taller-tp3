#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include "client_protocol.h"
#include "common_socket.h"

class Client {
    ClientProtocol protocol;
    Socket socket;

public:
    // Constructor
    // Asocia al cliente al 'host' y 'port' recibidos por consola
    Client(const char *host, const char *port);

    // Constructor y asignacion por copia deshabilitados
    Client(const Client& other) = delete;
    Client& operator=(const Client& other) = delete;

    // Determina si un comando recibido por stdin es valido o no
    const bool isValidCommand(const std::string& command) const;

    // Determina si un numero recibido por stdin es valido o no
    const bool isValidNumber(const std::string& command) const;

    // Interactua con el servidor (envia y recibe mensajes)
    void interactWithServer(const std::string& command);

    // Envia un mensaje al servidor
    void sendMessage(ByteMsg& byte_msg);

    // Recibe un mensaje del servidor
    void receiveMessage();
};

#endif // CLIENT_H
