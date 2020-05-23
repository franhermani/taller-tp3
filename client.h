#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include "client_protocol.h"

class Client {
    ClientProtocol protocol;

public:
    // Constructor
    Client();

    // Constructor y asignacion por copia deshabilitados
    Client(const Client& other) = delete;
    Client& operator=(const Client& other) = delete;

    // Determina si un comando recibido por stdin es valido o no
    const bool isValidCommand(const std::string command) const;

    // Determina si un numero recibido por stdin es valido o no
    const bool isValidNumber(const std::string command) const;

    // Interactua con el servidor (envia y recibe mensajes)
    void interactWithServer(const std::string command);
};

#endif // CLIENT_H
