#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>
#include "server_number_guesser.h"
#include "server_defines.h"
#include "server_out_of_range_error.h"

NumberGuesser::NumberGuesser(int number) : min_num(MIN_NUM), max_num(MAX_NUM) {
    if (! isInRange(number)) throw OutOfRangeError();

    secret_number = convertIntToVector(number);
}

bool NumberGuesser::isInRange(const int number) {
    return (number >= min_num && number <= max_num);
}

std::vector<int> NumberGuesser::convertIntToVector(int number) {
    std::vector<int> digits;

    while (number) {
        digits.push_back(number % 10);
        number /= 10;
    }
    std::reverse(digits.begin(), digits.end());

    return std::move(digits);
}

const std::map<std::string, int> NumberGuesser::countDigits(const int number) {
    std::map<std::string, int> answer = {{GOOD, 0}, {REGULAR, 0}, {BAD, 0}};
    std::vector<int> digits = convertIntToVector(number);

    size_t i;
    for (i = 0; i < secret_number.size(); i ++) {
        if (digits[i] == secret_number[i]) {
            answer[GOOD] += 1;
        } else {
            answer[REGULAR] += std::count(secret_number.begin(),
                                          secret_number.end(), digits[i]);
        }
    }
    if (answer[GOOD] == 0 && answer[REGULAR] == 0) answer[BAD] = NUM_DIGITS;

    return answer;
}
