#include <string.h>
#include <errno.h>
#include <cstdio>
#include <cstdarg>
#include "common_socket_error.h"

SocketError::SocketError(const char *fmt, ...) noexcept {
    int errno_aux = errno;
    va_list args;
    va_start(args, fmt);
    int s = vsnprintf(msgError, BUF_LEN, fmt, args);
    va_end(args);
    strncpy(msgError + s, strerror(errno_aux), BUF_LEN - s);
    msgError[BUF_LEN - 1] = '\0';
}

const char* SocketError::what() const noexcept {
    return msgError;
}
