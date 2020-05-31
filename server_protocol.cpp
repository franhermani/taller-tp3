#include <string.h>
#include <map>
#include <stdint.h>
#include <cstring>
#include <arpa/inet.h>
#include "server_protocol.h"
#include "server_defines.h"

ServerProtocol::ServerProtocol() {}

ByteMsg ServerProtocol::encodeMessage(const char *message) {
    cleanByteMsg();
    std::map<char, const char *> responses =
            {{HELP_CHAR, "Comandos válidos:\n\tAYUDA: despliega la lista de"
                         " comandos válidos\n\tRENDIRSE: pierde el juego"
                         " automáticamente\n\tXXX: Número de 3 cifras a ser"
                         " enviado al servidor para adivinar el número"
                         " secreto"}, {SURRENDER_CHAR, LOSE_MSG}};
    const char *response;
    if (message[0] == HELP_CHAR || message[0] == SURRENDER_CHAR) {
        response = responses[message[0]];
    } else {
        response = message;
    }
    writeMessageLength(response);
    writeMessageValue(response);
    return byteMsg;
}

void ServerProtocol::writeMessageLength(const char *message) {
    uint32_t length_network = htonl(strlen(message));
    memcpy(&byteMsg.value[byteMsg.pos], &length_network, sizeof(uint32_t));
    byteMsg.pos += sizeof(uint32_t);
}

void ServerProtocol::writeMessageValue(const char *message) {
    memcpy(&byteMsg.value[byteMsg.pos], message, strlen(message));
    byteMsg.pos += strlen(message);
}

std::string ServerProtocol::decodeMessageValue(const char *message) {
    uint16_t number = message[0] | (message[1] << 8);
    return std::to_string(ntohs(number));
}

uint32_t ServerProtocol::decodeMessageLength(const char *message) {
    std::map<char, uint32_t> lengths = {{HELP_CHAR, 0}, {SURRENDER_CHAR, 0},
                                        {NUMBER_CHAR, sizeof(uint16_t)}};

    return lengths[message[0]];
}
