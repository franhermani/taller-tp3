#include <iostream>

#define RET 0
#define NUM_PARAMS 3

int main(int argc, char *argv[]) {
    if (argc != NUM_PARAMS) {
        std::cerr << "Error: argumentos inválidos>\n";
        return RET;
    }
//    const char *host = argv[1], *port = argv[2];

    return RET;
}
