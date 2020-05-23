#include <string.h>
#include <map>
#include <stdint.h>
#include <cstring>
#include <arpa/inet.h>
#include "client_protocol.h"
#include "common_defines.h"

ClientProtocol::ClientProtocol() {}

ByteMsg ClientProtocol::encodeMessage(const std::string message) {
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

std::string ClientProtocol::decodeMessage(const char *byte_msg) {
    std::string message = "Hola mundo";
    return message;
}
