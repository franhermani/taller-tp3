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
        byteMsg.value[byteMsg.pos++] = HELP_CHAR;
    } else if (strcmp(message, SURRENDER) == 0) {
        byteMsg.value[byteMsg.pos++] = SURRENDER_CHAR;
    } else {
        byteMsg.value[byteMsg.pos++] = NUMBER_CHAR;
        uint16_t number_network = htons(atoi(message));
        memcpy(&byteMsg.value[byteMsg.pos], &number_network, sizeof(uint16_t));
        byteMsg.pos += sizeof(uint16_t);
    }
    return byteMsg;
}

std::string ClientProtocol::decodeMessageValue(const char *message) {
    std::string str(message);
    return str;
}

uint32_t ClientProtocol::decodeMessageLength(const char *message) {
    uint32_t length;
    memcpy(&length, message, sizeof(uint32_t));
    return ntohl(length);
}
