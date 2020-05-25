#include <exception>

#ifndef INVALID_NUMBER_ERROR_H
#define INVALID_NUMBER_ERROR_H

struct InvalidNumberError : public std::exception {
    const char * what() const throw() {
        return "Número inválido. Debe ser de 3 cifras no repetidas";
    }
};

#endif // INVALID_NUMBER_ERROR_H
