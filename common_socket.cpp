#define _POSIX_C_SOURCE 200112L

#include <iostream>
#include <string.h>
#include <unistd.h>
#include <utility>
#include "common_socket.h"
#include "common_socket_error.h"

#define OK 0
#define MAX_LISTEN_QUEUE_LEN 15

Socket::Socket(const char* host, const char* port) :
               sd(-1), is_server(host == 0) {
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = is_server ? AI_PASSIVE : 0;

    _resolve_addr(host, port);
}

Socket::Socket(const int sd) {
    this->sd = sd;
}

Socket::Socket(Socket &&other) {
    sd = std::move(other.sd);
}

Socket& Socket::operator=(Socket &&other) {
    sd = std::move(other.sd);
    return *this;
}

Socket::~Socket() {
    if (sd != -1) close(sd);
}

void Socket::shutdownChannel(const int channel) {
    if (shutdown(sd, channel) == -1)
        throw SocketError("Error al cerrar el canal %d del socket\n", channel);
}

void Socket::closeSocketDescriptor() {
    if (close(sd) == -1) throw SocketError("Error al cerrar el socket\n");
    sd = -1;
}

void Socket::_resolve_addr(const char *host, const char *port) {
    struct addrinfo *ai_list, *ptr;
    int sd, status;

    if ((status == getaddrinfo(host, port, &hints, &ai_list)) != 0)
        throw SocketError("Error en getaddrinfo: %s\n", gai_strerror(status));

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
    if (this->sd == -1) throw SocketError("No hay conexiones disponibles\n");
}

const int Socket::_bind(struct sockaddr *addr, const socklen_t len) {
    int val = 1;

    if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val)) == -1) {
        closeSocketDescriptor();
        throw SocketError("Error en setsockopt\n");
    }
    if (bind(sd, addr, len) == -1) {
        closeSocketDescriptor();
        throw SocketError("Error al enlazar el socket\n");
    }
    return OK;
}

const int Socket::_connect(struct sockaddr *addr, const socklen_t len) {
    if (connect(sd, addr, len) == -1) {
        closeSocketDescriptor();
        throw SocketError("Error al conectar con el servidor\n");
    }
    return OK;
}

void Socket::listenToClients() {
    if (listen(sd, MAX_LISTEN_QUEUE_LEN) == -1) {
        closeSocketDescriptor();
        throw SocketError("Error al escuchar clientes\n");
    }
}

Socket Socket::acceptClients() {
    int new_sd = accept(sd, NULL, NULL);
    if (new_sd == -1)
        throw SocketError("Error al aceptar el cliente\n");

    Socket accepted_socket(new_sd);
    return std::move(accepted_socket);
}

const int Socket::sendBytes(const char *buffer, const int length) {
    int tot_bytes_sent = 0, bytes_sent = 0;
    bool socket_closed = false, socket_error = false;

    while (tot_bytes_sent < length && (! socket_closed) && (! socket_error)) {
        bytes_sent = send(sd, &buffer[tot_bytes_sent], length - tot_bytes_sent,
                          MSG_NOSIGNAL);
        if (bytes_sent == -1) {
            socket_error = true;
        } else if (bytes_sent == 0) {
            socket_closed = true;
        } else {
            tot_bytes_sent += bytes_sent;
        }
    }
    if (socket_closed || socket_error) {
        shutdownChannel(SHUT_RDWR);
        closeSocketDescriptor();
        throw SocketError("Error al enviar el mensaje\n");
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
        throw SocketError("Error al recibir el mensaje\n");
    }
    return tot_bytes_recv;
}
