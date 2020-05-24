#include <vector>
#include <utility>
#include "server_thread_acceptor.h"
#include "server_thread_client.h"

ThreadAcceptor::ThreadAcceptor(const char *host, const char *port,
                               std::vector<ThreadClient*>& clients) :
socket(host, port), clients(clients) {}

void ThreadAcceptor::run() {
    // TODO: hasta que recibo el char 'q'
    while (true) {
        socket.listenToClients();
        Socket socket_client = socket.acceptClients();
        clients.push_back(new ThreadClient(std::move(socket_client)));
    }
}
