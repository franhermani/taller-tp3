#include <string.h>
#include <map>
#include <stdint.h>
#include <cstring>
#include <arpa/inet.h>
#include "client_protocol.h"
#include "common_defines.h"

ClientProtocol::ClientProtocol() {}

ByteMsg ClientProtocol::encodeMessage(const char *message) {
    cleanByteMsg();
    if (strcmp(message, HELP) == 0) {
        byteMsg.value[byteMsg.pos] = HELP_CHAR;
    } else if (strcmp(message, SURRENDER) == 0) {
        byteMsg.value[byteMsg.pos] = SURRENDER_CHAR;
    } else {
        byteMsg.value[byteMsg.pos] = NUMBER_CHAR;
        uint16_t number_network = htons(atoi(message));
        byteMsg.value[++byteMsg.pos] = (number_network & 0xFF);
        byteMsg.value[++byteMsg.pos] = (number_network >> 8);
    }
    return byteMsg;
}

std::string ClientProtocol::decodeMessageValue(const char *message) {
    std::string str(message);
    return str;
}

uint32_t ClientProtocol::decodeMessageLength(const char *message) {
    uint32_t length = message[0] | (message[1] << 8) |
            (message[2] << 16) | (message[3] << 24);

    return ntohl(length);
}
