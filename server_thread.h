#ifndef THREAD_H
#define THREAD_H

#include <thread>

class Thread {
    std::thread thread;

public:
    // Constructor
    Thread();

    // Inicializa el thread
    void start();

    // Ejecuta el thread (redefinido por sus clases derivadas)
    virtual void run() = 0;

    // Frena la ejecucion del thread (redefinido por sus clases derivadas)
    virtual void stop() = 0;

    // Indica el el thread esta corriendo o no
    // (redefinido por sus clases derivadas)
    virtual const bool isDead() = 0;

    // Espera a que finalice el thread
    void join();

    // Destructor
    virtual ~Thread();

    // Constructor y asignacion por copia deshabilitados
    Thread(const Thread&) = delete;
    Thread& operator=(const Thread&) = delete;

    // Constructor y asignacion por movimiento
    Thread(Thread&& other);
    Thread& operator=(Thread&& other);
};

#endif // THREAD_H
