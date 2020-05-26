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
    std::string response = receiveMessage();
    sendMessage(response);
}

const std::string ThreadClient::receiveMessage() {
    std::string response;
    char buffer_byte[BYTE_SIZE];
    socket.receiveBytes(buffer_byte, BYTE_SIZE);

    uint32_t length = protocol.decodeMessageLength(buffer_byte);
    if (length > 0) {
        int number = receiveNumber(length);
        response = processNumber(number);
    } else {
        std::string str(buffer_byte);
        response = str;
    }
    if (buffer_byte[0] == SURRENDER_CHAR) {
        gameStats.addLoser();
        is_finished = true;
    }
    if (is_finished) stop();

    return response;
}

void ThreadClient::sendMessage(const std::string& response) {
    ByteMsg byte_msg = protocol.encodeMessage(response.c_str());
    socket.sendBytes(byte_msg.value, byte_msg.pos + 1);
}

const int ThreadClient::receiveNumber(size_t length) {
    char buffer_number[NUMBER_SIZE];
    socket.receiveBytes(buffer_number, length);
    std::string number_str = protocol.decodeMessageValue(buffer_number);
    return stoi(number_str);
}

const std::string ThreadClient::processNumber(const int number) {
    std::string response;
    try {
        response = writeNumberAnswer(number);
    } catch(InvalidNumberError &e) {
        response = e.what();
    }
    num_tries += 1;

    if (num_tries == ATTEMPTS && response != WIN_MSG) {
        response = LOSE_MSG;
        gameStats.addLoser();
        is_finished = true;
    }
    if (is_finished) stop();

    return response;
}

const std::string ThreadClient::writeNumberAnswer(const int number) {
    std::string response;
    std::map<std::string, int> answer = numberGuesser(number);

    if (answer[GOOD] > 0) {
        if (answer[GOOD] == NUM_DIGITS) {
            response += WIN_MSG;
            gameStats.addWinner();
            is_finished = true;
        } else {
            response += std::to_string(answer[GOOD]) + GOOD;
        }
    }
    if (answer[REGULAR] > 0) {
        if (response.size() > 0) response += ", ";
        response += std::to_string(answer[REGULAR]) + REGULAR;
    }
    if (answer[BAD] > 0) response += std::to_string(answer[BAD]) + BAD;

    return response;
}
