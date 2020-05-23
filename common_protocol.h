#ifndef COMMON_PROTOCOL_H
#define COMMON_PROTOCOL_H

#include <string>
#include <stdint.h>

struct ByteMsg {
    uint8_t *value;
    int length;
    int pos;
};

class Protocol {
protected:
    ByteMsg byteMsg;

public:
    // Codifica un mensaje segun el protocolo
    // Metodo a definir por las clases derivadas
    virtual void encodeMessage(const char *message) = 0;

    // Decodifica un mensaje segun el protocolo
    // Metodo a definir por las clases derivadas
    virtual std::string decodeMessage(const char *byte_msg) = 0;
};

#endif // COMMON_PROTOCOL_H
