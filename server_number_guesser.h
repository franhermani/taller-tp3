#ifndef NUMBER_GUESSER_H
#define NUMBER_GUESSER_H

#include <string>
#include <vector>
#include <map>

class NumberGuesser {
    std::vector<int> secret_number;

    // Convierte un entero a un vector con sus digitos
    std::vector<int> convertIntToVector(int number);

public:
    // Constructor
    // Recibe un numero secreto
    explicit NumberGuesser(const int number);

    // Cuenta la cantidad de digitos bien, regular y mal de 'number'
    // con respecto a 'secret_number'
    // Devuelve un map con la cantidad correspondiente a cada categoria
    const std::map<std::string, int> countDigits(const int number);
};

#endif // NUMBER_GUESSER_H
