#include <fstream>
#include <string>
#include <exception>
#include <iostream>
#include "server_file.h"

File::File(const char *path) {
    ifs.open(path, std::ifstream::in);
    if (! ifs.good()) throw std::runtime_error("Error al abrir el archivo\n");
    is_open = true;
}

File::~File() {
    if (is_open) closeFD();
}

void File::closeFD() {
    ifs.close();
    is_open = false;
}

std::ifstream& File::getFile() {
    return ifs;
}
