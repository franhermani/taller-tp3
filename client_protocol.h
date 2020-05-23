#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include <string>
#include <stdint.h>
#include "common_protocol.h"

class ClientProtocol : public Protocol {
public:
    // Constructor
    ClientProtocol();

    // Constructor y asignacion por copia deshabilitados
    ClientProtocol(const ClientProtocol&) = delete;
    ClientProtocol& operator=(const ClientProtocol&) = delete;

    // Codifica un mensaje segun el protocolo
    virtual ByteMsg encodeMessage(const char *message) override;

    // Decodifica un mensaje segun el protocolo
    virtual std::string decodeMessageValue(const char *message) override;

    // Decodifica el largo del string a recibir
    // Devuelve el largo en un entero de 4 bytes
    virtual uint32_t decodeMessageLength(const char *message) override;
};

#endif // CLIENT_PROTOCOL_H
