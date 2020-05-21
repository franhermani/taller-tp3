#ifndef FILE_H
#define FILE_H

#include <fstream>
#include <string>

class File {
    std::ifstream ifs;
    bool is_open;

public:
    // Constructor
    // Abre el archivo
    explicit File(const char *path);

    // Destructor
    // Cierra el archivo si no se pudo cerrar antes
    ~File();

    // Cierra el archivo
    void closeFD();

    // Lee una linea del archivo y la almacena en 'line'
    // Devuelve true siempre y cuando la linea leida no tenga longitud nula
    bool readLine(std::string& line);
};

#endif // FILE_H
