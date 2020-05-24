#include "server_thread_acceptor.h"

ThreadAcceptor::ThreadAcceptor(const char *host, const char *port) :
socket(host, port) {}

void ThreadAcceptor::run() {
    // TODO: ...
}
