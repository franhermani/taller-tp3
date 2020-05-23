#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <string>
#include <stdint.h>
#include "common_protocol.h"

class ServerProtocol : public Protocol {
public:
    // Constructor
    ServerProtocol();

    // Constructor y asignacion por copia deshabilitados
    ServerProtocol(const ServerProtocol&) = delete;
    ServerProtocol& operator=(const ServerProtocol&) = delete;

    // Codifica un mensaje segun el protocolo
    virtual ByteMsg encodeMessage(const char *message) override;

    // Decodifica un mensaje segun el protocolo
    virtual std::string decodeMessageValue(const char *message) override;

    // Decodifica el largo del string a recibir
    // Devuelve el largo en un entero de 4 bytes
    virtual uint32_t decodeMessageLength(const char *message) override;
};

#endif // SERVER_PROTOCOL_H
