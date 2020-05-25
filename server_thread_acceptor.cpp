#include <iostream>
#include <vector>
#include <utility>
#include "server_thread_acceptor.h"
#include "server_thread_client.h"
#include "common_socket_error.h"

ThreadAcceptor::ThreadAcceptor(const char *host, const char *port,
        std::vector<NumberGuesser>& numbers, GameStats& game_stats) :
        socket(host, port), numbers(numbers), gameStats(game_stats),
        keep_talking(true), is_running(true) {}

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
            numbers[pos], gameStats));
}

void ThreadAcceptor::cleanDeadClients() {
    /*
    std::vector<ThreadClient*>::iterator iter = clients.begin();
    while (iter != clients.end()) {
        if ((*iter)->isDead()) {
            (*iter)->join();
            delete (*iter);
            iter = clients.erase(iter);
        } else {
            iter++;
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
