#include <string>
#include <iostream>
#include "server_thread_input.h"
#include "server_defines.h"

ThreadInput::ThreadInput() {}

void ThreadInput::run() {
    std::string command;
    while (getline(std::cin, command)) {
        if (command == EXIT_CHAR) {
            // TODO: matar al thread acceptor
            // TODO: esperar a que terminen todos los clientes (join)
            break;
        }
    }
}
