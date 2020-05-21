#include <iostream>

#define OK 0
#define ERROR 1
#define NUM_PARAMS 3

int main(int argc, char *argv[]) {
    if (argc != NUM_PARAMS) {
        std::cerr << "Error: argumentos inválidos>\n";
        return ERROR;
    }
//    const char *host = 0, *port = argv[1], *file_path = argv[2];

    return OK;
}
