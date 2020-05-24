#include <iostream>
#include <vector>
#include <utility>
#include "server_thread_acceptor.h"
#include "server_thread_client.h"
#include "common_socket_error.h"

ThreadAcceptor::ThreadAcceptor(const char *host, const char *port,
        std::vector<NumberGuesser>& numbers) : socket(host, port),
        numbers(numbers), keep_talking(true), is_running(true) {}

void ThreadAcceptor::run() {
    while (keep_talking) {
        try {
            socket.listenToClients();
            createThreadClient();
            clients.back()->start();
            cleanDeadClients();
        } catch(SocketError) {
            break;
        }
    }
    is_running = false;
    joinClients();
}

void ThreadAcceptor::stop() {
    keep_talking = false;
    socket.finish();
}

const bool ThreadAcceptor::isDead() {
    return (! is_running);
}

void ThreadAcceptor::createThreadClient() {
    Socket socket_client = socket.acceptClients();
    int pos = clients.size() % numbers.size();
    clients.push_back(new ThreadClient(std::move(socket_client),
            numbers[pos]));
}

void ThreadAcceptor::cleanDeadClients() {
    // TODO: descomentar esto cuando ande todo (y corregir el erase)
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

void ThreadAcceptor::joinClients() {
    size_t i;
    for (i = 0; i < clients.size(); i ++) {
        clients[i]->join();
        delete clients[i];
    }
}
