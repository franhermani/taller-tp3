#ifndef SOCKET_ERROR_H
#define SOCKET_ERROR_H

#include <exception>
#include <typeinfo>

#define BUF_LEN 256

class SocketError : public std::exception {
    char msg_error[BUF_LEN];

public:
    explicit SocketError(const char *fmt, ...) noexcept;
    virtual const char *what() const noexcept;
};

#endif // SOCKET_ERROR_H
