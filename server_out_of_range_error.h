#include <exception>

#ifndef OUT_OF_RANGE_ERROR_H
#define OUT_OF_RANGE_ERROR_H

struct OutOfRangeError : public std::exception {
    const char * what() const throw() {
        return "Error: archivo con números fuera de rango\n";
    }
};

#endif // OUT_OF_RANGE_ERROR_H
