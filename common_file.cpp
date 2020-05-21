#include <fstream>
#include <string>
#include <exception>
#include <iostream>
#include "common_file.h"

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

bool File::readLine(std::string& line) {
    getline(ifs, line);
    return (line.size() != 0);
}
