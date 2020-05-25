#include <iostream>
#include <string>
#include <string.h>
#include <map>
#include <utility>
#include "server_thread_client.h"
#include "server_defines.h"
#include "server_invalid_number_error.h"
#include "common_socket_error.h"

#define BYTE_SIZE 1
#define NUMBER_SIZE 2

ThreadClient::ThreadClient(Socket socket, NumberGuesser& number_guesser,
        GameStats& game_stats) : socket(std::move(socket)),
        numberGuesser(number_guesser), gameStats(game_stats),
        keep_talking(true), is_running(true), is_finished(false),
        num_tries(0) {}

void ThreadClient::run() {
    while (keep_talking) {
        try {
            interactWithClient();
        } catch(SocketError) {
            break;
        }
    }
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

        if (buffer_byte[0] == SURRENDER_CHAR) {
            gameStats.addLoser();
            is_finished = true;
        }
    }
    if (is_finished) stop();
}

void ThreadClient::processClientNumber(const int number) {
    std::string message;
    try {
        std::map<std::string, int> answer = numberGuesser(number);

        if (answer[GOOD] > 0) {
            if (answer[GOOD] == NUM_DIGITS) {
                message += WIN_MSG;
                gameStats.addWinner();
                is_finished = true;
            } else {
                message += std::to_string(answer[GOOD]) + GOOD;
            }
        }
        if (answer[REGULAR] > 0) {
            if (message.size() > 0) message += ", ";
            message += std::to_string(answer[REGULAR]) + REGULAR;
        }
        if (answer[BAD] > 0) message += std::to_string(answer[BAD]) + BAD;
    } catch(InvalidNumberError &e) {
        message = e.what();
    }
    num_tries += 1;
    if (num_tries == ATTEMPTS) {
        message = LOSE_MSG;
        gameStats.addLoser();
        is_finished = true;
    }
    ByteMsg byte_msg = protocol.encodeMessage(message.c_str());
    socket.sendBytes(byte_msg.value, byte_msg.pos + 1);

    if (is_finished) stop();
}
