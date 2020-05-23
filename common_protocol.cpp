#include <string.h>
#include "common_protocol.h"

void Protocol::cleanByteMsg() {
    memset(byteMsg.value, 0, MSG_MAX_SIZE);
    byteMsg.pos = 0;
}
