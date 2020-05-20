#include <iostream>
#include <string>
#include <map>
#include <exception>
#include "server_number_guesser.h"
#include "server_defines.h"

#define OK 0
#define ERROR 1

int main(int argc, char *argv[]) {
    try {
        int secret_number = 1200;
        NumberGuesser numberGuesser(secret_number);

        int n = 132;
        std::map<std::string, int> answer = numberGuesser.countDigits(n);

        std::cout << answer[GOOD] << GOOD << ", " << answer[REGULAR] << REGULAR
                  << ", " << answer[BAD] << BAD << "\n";
    } catch(const std::exception &e) {
        std::cout << e.what();
    } catch(...) {
        std::cout << "Error desconocido\n";
    }
    return OK;
}
