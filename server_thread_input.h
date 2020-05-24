#ifndef THREAD_INPUT_H
#define THREAD_INPUT_H

#include "server_thread.h"

class ThreadInput : public Thread {
public:
    // Constructor
    ThreadInput();

    // Constructor y asignacion por copia deshabilitados
    ThreadInput(const ThreadInput&) = delete;
    ThreadInput& operator=(const ThreadInput&) = delete;

    virtual void run() override;
};


#endif // THREAD_INPUT_H
