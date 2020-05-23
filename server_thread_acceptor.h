#ifndef THREAD_ACCEPTOR_H
#define THREAD_ACCEPTOR_H

#include "server_thread.h"

class ThreadAcceptor : public Thread {
public:
    // Constructor y asignacion por copia deshabilitados
    ThreadAcceptor(const ThreadAcceptor&) = delete;
    ThreadAcceptor& operator=(const ThreadAcceptor&) = delete;
};

#endif // THREAD_ACCEPTOR_H
