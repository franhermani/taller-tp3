#ifndef NUMBER_GUESSER_H
#define NUMBER_GUESSER_H

#include <vector>

class NumberGuesser {
    std::vector<int> secret_number;

    // Convierte un entero a un vector con sus digitos
    std::vector<int> convertIntToVector(int number);

public:
    // Constructor
    explicit NumberGuesser(const int number);

    // Cuenta la cantidad de digitos de 'number' que concuerdan en valor
    // y posicion con 'secret_number'
    const int countGoodDigits(const int number);

    // Cuenta la cantidad de digitos de 'number' que concuerdan en valor
    // pero no en posicion con 'secret_number'
    const int countRegularDigits(const int number);

    const int countBadDigits(const int number);
};

#endif // NUMBER_GUESSER_H
