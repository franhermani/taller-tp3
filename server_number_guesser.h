#ifndef NUMBER_GUESSER_H
#define NUMBER_GUESSER_H

#include <string>
#include <vector>
#include <map>

class NumberGuesser {
    std::vector<int> secretNumber;

    // Determina si 'number' se encuentra fuera del rango valido
    const bool isOutOfRange(const int& number) const;

    // Convierte un entero a un vector con sus digitos
    const std::vector<int> convertIntToVector(int number) const;

    // Determina si 'number' tiene cifras repetidas
    const bool hasRepeatedDigits(const std::vector<int>& digits) const;

public:
    // Constructor
    // Recibe un numero secreto
    explicit NumberGuesser(int number);

    // Constructor y asignacion por copia deshabilitados
    NumberGuesser(const NumberGuesser&) = delete;
    NumberGuesser& operator=(const NumberGuesser&) = delete;

    // Constructor por movimiento
    NumberGuesser(NumberGuesser&& other);

    // Cuenta la cantidad de digitos bien, regular y mal de 'number'
    // con respecto a 'secretNumber'
    // Devuelve un map con la cantidad correspondiente a cada categoria
    const std::map<std::string, int> operator()(const int number) const;
};

#endif // NUMBER_GUESSER_H
