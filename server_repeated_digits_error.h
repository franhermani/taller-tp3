#include <exception>

#ifndef REPEATED_DIGITS_ERROR_H
#define REPEATED_DIGITS_ERROR_H

struct RepeatedDigitsError : public std::exception {
    const char * what() const throw() {
        return "Error: formato de los números inválidos\n";
    }
};

#endif // REPEATED_DIGITS_ERROR_H
