#include <vector>
#include <utility>
#include "server_thread_acceptor.h"
#include "server_thread_client.h"
#include "common_socket_error.h"

ThreadAcceptor::ThreadAcceptor(const char *host, const char *port) :
socket(host, port), keep_talking(true), is_running(true) {}

ThreadAcceptor::~ThreadAcceptor() {
    size_t i;
    for (i = 0; i < clients.size(); i ++) {
        clients[i]->join();
        delete clients[i];
    }
}

void ThreadAcceptor::run() {
    while (keep_talking) {
        try {
            socket.listenToClients();
            Socket socket_client = socket.acceptClients();
            clients.push_back(new ThreadClient(std::move(socket_client)));
            clients.back()->start();
            cleanDeadClients();
        } catch(SocketError) {
            break;
        }
    }
    is_running = false;
}

void ThreadAcceptor::stop() {
    keep_talking = false;
    socket.finish();
}

const bool ThreadAcceptor::isDead() {
    return (! is_running);
}

void ThreadAcceptor::cleanDeadClients() {
    // TODO: descomentar esto cuando ande todo
    // ojo que el erase creo que esta mal
    /*
    size_t i;
    for (i = 0; i < clients.size(); i ++) {
        if (clients[i]->isDead()) {
            clients[i]->join();
            delete clients[i];
            clients.erase(clients.begin() + i);
        }
    }
    */
}
