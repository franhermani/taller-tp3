#include <utility>
#include "server_thread_client.h"

ThreadClient::ThreadClient(Socket socket) : socket(std::move(socket)) {}

void ThreadClient::run() {
    // TODO: ...
}
