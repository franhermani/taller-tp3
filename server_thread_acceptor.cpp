#include <vector>
#include <utility>
#include "server_thread_acceptor.h"
#include "server_thread_client.h"
#include "common_socket_error.h"

ThreadAcceptor::ThreadAcceptor(const char *host, const char *port,
        std::vector<NumberGuesser>& numbers, GameStats& game_stats) :
        socket(host, port), numbers(numbers), gameStats(game_stats),
        keep_talking(true), is_running(true), actual_number_pos(0) {}

void ThreadAcceptor::run() {
    while (keep_talking) {
        try {
            socket.listenToClients();
            createThreadClient();
            startThreadClient();
            cleanDeadClients();
            updateNumberPos();
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
    clients.push_back(new ThreadClient(std::move(socket_client),
            numbers[actual_number_pos], gameStats));
}

void ThreadAcceptor::startThreadClient() {
    clients.back()->start();
}

void ThreadAcceptor::cleanDeadClients() {
    std::vector<ThreadClient*> tmp;
    std::vector<ThreadClient*>::iterator iter = clients.begin();
    for (; iter != clients.end(); ++iter) {
        if ((*iter)->isDead()) {
            (*iter)->join();
            delete (*iter);
        } else {
            tmp.push_back((*iter));
        }
    }
    clients.swap(tmp);
}

void ThreadAcceptor::joinClients() {
    size_t i;
    for (i = 0; i < clients.size(); i ++) {
        clients[i]->join();
        delete clients[i];
    }
}

void ThreadAcceptor::updateNumberPos() {
    if (actual_number_pos == (int) (numbers.size() - 1)) {
        actual_number_pos = 0;
    } else {
        actual_number_pos ++;
    }
}
