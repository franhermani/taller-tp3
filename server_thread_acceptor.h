#ifndef THREAD_ACCEPTOR_H
#define THREAD_ACCEPTOR_H

#include "server_thread.h"
#include "common_socket.h"

class ThreadAcceptor : public Thread {
    Socket socket;

public:
    // Constructor y asignacion por copia deshabilitados
    ThreadAcceptor(const ThreadAcceptor&) = delete;
    ThreadAcceptor& operator=(const ThreadAcceptor&) = delete;

    virtual void run() override;
};

#endif // THREAD_ACCEPTOR_H
