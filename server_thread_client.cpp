#include <string>
#include <map>
#include <utility>
#include "server_thread_client.h"
#include "server_defines.h"
#include "server_invalid_number_error.h"

#define BYTE_SIZE 1
#define NUMBER_SIZE 2

ThreadClient::ThreadClient(Socket socket, NumberGuesser& number_guesser) :
socket(std::move(socket)), numberGuesser(number_guesser),
keep_talking(true), is_running(true) {}

void ThreadClient::run() {
    while (keep_talking) interactWithClient();
    is_running = false;
}

void ThreadClient::stop() {
    keep_talking = false;
}

const bool ThreadClient::isDead() {
    return (! is_running);
}

void ThreadClient::interactWithClient() {
    char buffer_byte[BYTE_SIZE];
    socket.receiveBytes(buffer_byte, BYTE_SIZE);

    uint32_t length = protocol.decodeMessageLength(buffer_byte);
    if (length > 0) {
        char buffer_number[NUMBER_SIZE];
        socket.receiveBytes(buffer_number, length);
        std::string number_str = protocol.decodeMessageValue(buffer_number);
        processClientNumber(stoi(number_str));
    } else {
        ByteMsg byte_msg = protocol.encodeMessage(buffer_byte);
        socket.sendBytes(byte_msg.value, byte_msg.pos + 1);
    }
}

void ThreadClient::processClientNumber(const int number) {
    std::string message;
    try {
        std::map<std::string, int> answer = numberGuesser.countDigits(number);

        if (answer[GOOD] > 0) message += std::to_string(answer[GOOD]) + GOOD;

        if (answer[REGULAR] > 0) {
            if (message.size() > 0) message += ", ";
            message += std::to_string(answer[REGULAR]) + REGULAR;
        }
        if (answer[BAD] > 0) message += std::to_string(answer[BAD]) + BAD;
    } catch(InvalidNumberError &e) {
        message = e.what();
    }
    ByteMsg byte_msg = protocol.encodeMessage(message.c_str());
    socket.sendBytes(byte_msg.value, byte_msg.pos + 1);
}
