#include <vector>
#include <utility>
#include "server_thread_acceptor.h"
#include "server_thread_client.h"

ThreadAcceptor::ThreadAcceptor(const char *host, const char *port) :
socket(host, port), keep_talking(true), is_running(true) {}

void ThreadAcceptor::run() {
    while (keep_talking) {
        socket.listenToClients();
        Socket socket_client = socket.acceptClients();
        clients.push_back(new ThreadClient(std::move(socket_client)));
        clients.back()->start();
        // TODO: recorrer arreglo de clientes y limpiar los que esten muertos
    }
    is_running = false;
}

void ThreadAcceptor::stop() {
    keep_talking = false;
}

const bool ThreadAcceptor::isDead() {
    return (! is_running);
}
