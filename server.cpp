#include <iostream>
#include <exception>
#include "server_orchestrator.h"

#define OK 0
#define ERROR 1
#define NUM_PARAMS 3

int main(int argc, char *argv[]) {
    if (argc != NUM_PARAMS) {
        std::cerr << "Error: argumentos inválidos>\n";
        return ERROR;
    }
    ServerOrchestrator orchestrator;
    const char *host = 0, *port = argv[1], *path = argv[2];

    try {
        orchestrator.parseNumbersFile(path);
    } catch(const std::exception &e) {
        std::cerr << e.what();
    } catch(...) {
        std::cerr << "Error desconocido\n";
    }

    // TODO: eliminar esto
    std::cout << host << "\n";
    std::cout << port << "\n";

    return OK;
}
