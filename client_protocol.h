#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include <string>
#include "common_protocol.h"

class ClientProtocol : public Protocol {
public:
    // Constructor
    ClientProtocol();

    // Codifica un mensaje segun el protocolo
    virtual ByteMsg encodeMessage(const std::string message) override;

    // Decodifica un mensaje segun el protocolo
    virtual std::string decodeMessage(const char *byte_msg) override;
};

#endif // CLIENT_PROTOCOL_H
