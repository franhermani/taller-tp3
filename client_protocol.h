#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include <string>
#include "common_protocol.h"

class ClientProtocol : public Protocol {
public:
    // Codifica un mensaje segun el protocolo
    virtual void encodeMessage(const char *message) override;

    // Decodifica un mensaje segun el protocolo
    virtual std::string decodeMessage(const char *byte_msg) override;
};

#endif // CLIENT_PROTOCOL_H
