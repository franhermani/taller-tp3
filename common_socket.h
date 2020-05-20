#ifndef SOCKET_H
#define SOCKET_H

#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>

class Socket {
    int sd;
    struct addrinfo hints;
    bool is_server;

    const int _resolve_addr(const char *host, const char *port);

    const int _bind(struct sockaddr *addr, const socklen_t len);

    const int _connect(struct sockaddr *addr, const socklen_t len);

public:
    // Constructor
    Socket(const char *host, const char *port);

    // Destructor
    ~Socket();

    const int shutdownChannel(const int channel);

    const int closeSocketDescriptor();

    const int listenToClients();

    const int acceptClients(Socket& accepted_socket);

    const int sendBytes(const char *buffer, const int length);

    const int receiveBytes(char *buffer, const int length);
};


#endif // SOCKET_H
