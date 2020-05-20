#define _POSIX_C_SOURCE 200112L

#include <iostream>
#include <string.h>
#include <unistd.h>
#include "common_socket.h"

#define OK 0
#define ERROR 1
#define MAX_LISTEN_QUEUE_LEN 15

Socket::Socket(const char* host, const char* port) :
               sd(-1), is_server(host == 0) {
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = is_server ? AI_PASSIVE : 0;

    _resolve_addr(host, port);
}

Socket::~Socket() {
    if (sd != -1) close(sd);
}

const int Socket::shutdownChannel(const int channel) {
    if (shutdown(sd, channel) == -1) {
        std::cout << "Error: " << strerror(errno) << "\n";
        return ERROR;
    }
    return OK;
}

const int Socket::closeSocketDescriptor() {
    if (close(sd) == -1) {
        std::cout << "Error: " << strerror(errno) << "\n";
        return ERROR;
    }
    sd = -1;
    return OK;
}

const int Socket::_resolve_addr(const char *host, const char *port) {
    struct addrinfo *ai_list, *ptr;
    int sd, status;

    if ((status == getaddrinfo(host, port, &hints, &ai_list)) != 0) {
        std::cout << "Error en getaddrinfo: " << gai_strerror(status) << "\n";
        return ERROR;
    }
    for (ptr = ai_list; ptr != NULL; ptr = ptr->ai_next) {
        sd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (sd == -1) continue;

        this->sd = sd;
        if (is_server) {
            if (_bind(ptr->ai_addr, ptr->ai_addrlen) == OK) break;
        } else {
            if (_connect(ptr->ai_addr, ptr->ai_addrlen) == OK) break;
        }
    }
    freeaddrinfo(ai_list);

    if (this->sd == -1) {
        std::cout << "No hay conexiones disponibles\n";
        return ERROR;
    }
    return OK;
}

const int Socket::_bind(struct sockaddr *addr, const socklen_t len) {
    int val = 1;

    if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val)) == -1) {
        closeSocketDescriptor();
        std::cout << "Error: " << strerror(errno) << "\n";
        return ERROR;
    }
    if (bind(sd, addr, len) == -1) {
        closeSocketDescriptor();
        std::cout << "Error: " << strerror(errno) << "\n";
        return ERROR;
    }
    return OK;
}

const int Socket::_connect(struct sockaddr *addr, const socklen_t len) {
    if (connect(sd, addr, len) == -1) {
        closeSocketDescriptor();
        std::cout << "Error: " << strerror(errno) << "\n";
        return ERROR;
    }
    return OK;
}

const int Socket::listenToClients() {
    if (listen(sd, MAX_LISTEN_QUEUE_LEN) == -1) {
        closeSocketDescriptor();
        std::cout << "Error: " << strerror(errno) << "\n";
        return ERROR;
    }
    return OK;
}

const int Socket::sendBytes(const char *buffer, const int length) {
    int tot_bytes_sent = 0, bytes_sent = 0;
    bool socket_closed = false, socket_error = false;

    while (tot_bytes_sent < length && (! socket_closed) && (! socket_error)) {
        bytes_sent = send(sd, &buffer[tot_bytes_sent], length - tot_bytes_sent,
                          MSG_NOSIGNAL);
        if (bytes_sent == -1) {
            std::cout << "Error: " << strerror(errno) << "\n";
            socket_error = true;
        } else if (bytes_sent == 0) {
            std::cout << "Error: el socket se cerro inesperadamente\n";
            socket_closed = true;
        } else {
            tot_bytes_sent += bytes_sent;
        }
    }
    if (socket_closed || socket_error) {
        shutdownChannel(SHUT_RDWR);
        closeSocketDescriptor();
        return ERROR;
    }
    return tot_bytes_sent;
}

const int Socket::receiveBytes(char *buffer, const int length) {
    int tot_bytes_recv = 0, bytes_recv = 0;
    bool socket_closed = false, socket_error = false;

    while ((! socket_closed) && (! socket_error)) {
        bytes_recv = recv(sd, &buffer[tot_bytes_recv],
                          length - tot_bytes_recv, 0);
        if (bytes_recv == -1) {
            std::cout << "Error: " << strerror(errno) << "\n";
            socket_error = true;
        } else if (bytes_recv == 0) {
            socket_closed = true;
        } else {
            tot_bytes_recv += bytes_recv;
        }
    }
    if (socket_error) {
        shutdownChannel(SHUT_RDWR);
        closeSocketDescriptor();
        return ERROR;
    }
    return tot_bytes_recv;
}
