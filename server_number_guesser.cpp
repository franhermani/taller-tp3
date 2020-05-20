#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include "server_number_guesser.h"

NumberGuesser::NumberGuesser(const int number) :
secret_number(convertIntToVector(number)) {}

std::vector<int> NumberGuesser::convertIntToVector(int number) {
    std::vector<int> digits;

    while (number) {
        digits.push_back(number % 10);
        number /= 10;
    }
    std::reverse(digits.begin(), digits.end());

    return std::move(digits);
}

const int NumberGuesser::countGoodDigits(const int number) {
    return 0;
}

const int NumberGuesser::countRegularDigits(const int number) {
    return 0;
}

const int NumberGuesser::countBadDigits(const int number) {
    return 0;
}
