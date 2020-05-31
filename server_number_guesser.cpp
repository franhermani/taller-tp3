#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <utility>
#include "server_number_guesser.h"
#include "server_defines.h"
#include "server_out_of_range_error.h"
#include "server_repeated_digits_error.h"
#include "server_invalid_number_error.h"

NumberGuesser::NumberGuesser(int number) {
    if (isOutOfRange(number)) throw OutOfRangeError();
    secretNumber = convertIntToVector(number);
    if (hasRepeatedDigits(secretNumber)) throw RepeatedDigitsError();
}

NumberGuesser::NumberGuesser(NumberGuesser &&other) {
    secretNumber = std::move(other.secretNumber);
}

const bool NumberGuesser::isOutOfRange(const int& number) const {
    return (number < MIN_NUM || number > MAX_NUM);
}

const bool NumberGuesser::hasRepeatedDigits(const std::vector<int>& digits)
const {
    std::set<int> unique_digits(digits.begin(), digits.end());

    return (unique_digits.size() != digits.size());
}

const std::vector<int> NumberGuesser::convertIntToVector(int number) const {
    std::vector<int> digits;

    while (number) {
        digits.push_back(number % 10);
        number /= 10;
    }
    std::reverse(digits.begin(), digits.end());

    return std::move(digits);
}

const std::map<std::string, int> NumberGuesser::operator()(const int number)
const {
    if (isOutOfRange(number)) throw InvalidNumberError();
    std::vector<int> digits = convertIntToVector(number);
    if (hasRepeatedDigits(digits)) throw InvalidNumberError();

    std::map<std::string, int> answer = {{GOOD, 0}, {REGULAR, 0}, {BAD, 0}};
    size_t i;
    for (i = 0; i < secretNumber.size(); i ++) {
        if (digits[i] == secretNumber[i]) {
            answer[GOOD] += 1;
        } else {
            answer[REGULAR] += std::count(secretNumber.begin(),
                                          secretNumber.end(), digits[i]);
        }
    }
    if (answer[GOOD] == 0 && answer[REGULAR] == 0) answer[BAD] = NUM_DIGITS;

    return answer;
}
