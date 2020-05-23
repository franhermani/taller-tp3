#include <string.h>
#include <map>
#include <stdint.h>
#include <cstring>
#include <arpa/inet.h>
#include "server_protocol.h"
#include "server_defines.h"

ServerProtocol::ServerProtocol() {}

ByteMsg ServerProtocol::encodeMessage(const std::string message) {
    cleanByteMsg();
    std::map<std::string, char> commands =
            {{HELP, HELP_CHAR}, {SURRENDER, SURRENDER_CHAR}};

    if (commands.count(message)) {
        byteMsg.value[byteMsg.pos] = commands[message];
    } else {
        byteMsg.value[byteMsg.pos] = NUMBER_CHAR;
        uint16_t number_network = htons(atoi(message.c_str()));
        byteMsg.value[++byteMsg.pos] = number_network & 0xFF;
        byteMsg.value[++byteMsg.pos] = (number_network >> 8);
    }
    byteMsg.value[++byteMsg.pos] = '\0';

    return byteMsg;
}

std::string ServerProtocol::decodeMessageValue(const char *message) {
    std::string hello = "Hola mundo";
    return hello;
}

uint32_t ServerProtocol::decodeMessageLength(const char *message) {
    return ntohl(atoi(message));
}
