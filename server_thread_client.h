#ifndef THREAD_CLIENT_H
#define THREAD_CLIENT_H

#include "server_thread.h"

class ThreadClient : public Thread {
public:
    // Constructor y asignacion por copia deshabilitados
    ThreadClient(const ThreadClient&) = delete;
    ThreadClient& operator=(const ThreadClient&) = delete;
};

#endif // THREAD_CLIENT_H
