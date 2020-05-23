#ifndef CLIENT_ORCHESTRATOR_H
#define CLIENT_ORCHESTRATOR_H

#include <string>
#include "client_protocol.h"

class ClientOrchestrator {
    ClientProtocol protocol;

    // Determina si un numero recibido por stdin es valido o no
    const bool isValidNumber(const std::string command) const;

public:
    // Constructor
    ClientOrchestrator();

    // Constructor y asignacion por copia deshabilitados
    ClientOrchestrator(const ClientOrchestrator& other) = delete;
    ClientOrchestrator& operator=(const ClientOrchestrator& other) = delete;

    // Determina si un comando recibido por stdin es valido o no
    const bool isValidCommand(const std::string command) const;

    // Codifica el comando segun el protocolo
    ByteMsg encodeMessage(const std::string command);

    // Decodifica la longitud de un mensaje segun el protocolo
    uint32_t decodeMessageLength(const char *message);

    // Decodifica el contenido de un mensaje segun el protocolo
    std::string decodeMessageValue(const char *message);
};

#endif // CLIENT_ORCHESTRATOR_H
