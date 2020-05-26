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
    byteMsg.value[byteMsg.pos] = (length_network & 0x000000FF);
    byteMsg.value[++byteMsg.pos] = (length_network & 0x0000FF00) >> 8;
    byteMsg.value[++byteMsg.pos] = (length_network & 0x00FF0000) >> 16;
    byteMsg.value[++byteMsg.pos] = (length_network & 0xFF000000) >> 24;
}

void ServerProtocol::writeMessageValue(const char *message) {
    size_t i;
    for (i = 0; i < strlen(message); i ++)
        byteMsg.value[++byteMsg.pos] = message[i];
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
