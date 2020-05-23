#ifndef COMMON_PROTOCOL_H
#define COMMON_PROTOCOL_H

#include <string>

#define MSG_MAX_SIZE 256

struct ByteMsg {
    char value[MSG_MAX_SIZE];
    int pos;
};

class Protocol {
protected:
    ByteMsg byteMsg;

    // Limpia el struct ByteMsg llenándolo con ceros y reseteando sus atributos
    void cleanByteMsg();

public:
    // Codifica un mensaje segun el protocolo
    // Metodo a definir por las clases derivadas
    virtual ByteMsg encodeMessage(const std::string message) = 0;

    // Decodifica el contenido de un mensaje segun el protocolo
    // Metodo a definir por las clases derivadas
    virtual std::string decodeMessageValue(const char *message) = 0;

    // Decodifica la longitud de un mensaje segun el protocolo
    // Metodo a definir por las clases derivadas
    virtual uint32_t decodeMessageLength(const char *message) = 0;
};

#endif // COMMON_PROTOCOL_H
