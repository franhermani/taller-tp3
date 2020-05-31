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
        keepTalking(true), isRunning(true), isFinished(false),
        numTries(0) {}

void ThreadClient::run() {
    while (keepTalking) {
        try {
            interactWithClient();
        } catch(SocketError) {
            break;
        }
    }
    isRunning = false;
}

void ThreadClient::stop() {
    keepTalking = false;
}

const bool ThreadClient::isDead() {
    return (! isRunning);
}

void ThreadClient::interactWithClient() {
    std::string response = receiveMessage();
    sendMessage(response);
    if (isFinished) stop();
}

const std::string ThreadClient::receiveMessage() {
    std::string response;
    char buffer[BYTE_SIZE];
    socket.receiveBytes(buffer, BYTE_SIZE);

    uint32_t length = protocol.decodeMessageLength(buffer);
    if (length > 0) {
        numTries += 1;
        int number = receiveNumber(length);
        response = processNumber(number);
    } else {
        std::string str(buffer);
        response = str;
        if (buffer[0] == SURRENDER_CHAR) lose();
    }
    return response;
}

void ThreadClient::sendMessage(const std::string& response) {
    ByteMsg byte_msg = protocol.encodeMessage(response.c_str());
    socket.sendBytes(byte_msg.value, byte_msg.pos);
}

const int ThreadClient::receiveNumber(size_t length) {
    char buffer[NUMBER_SIZE];
    socket.receiveBytes(buffer, length);
    std::string number_str = protocol.decodeMessageValue(buffer);
    return stoi(number_str);
}

const std::string ThreadClient::processNumber(const int number) {
    std::string response;
    try {
        response = writeNumberAnswer(number);
    } catch(InvalidNumberError &e) {
        response = e.what();
    }
    if (numTries == ATTEMPTS && response != WIN_MSG) {
        response = LOSE_MSG;
        lose();
    }
    return response;
}

const std::string ThreadClient::writeNumberAnswer(const int number) {
    std::string response;
    std::map<std::string, int> answer = numberGuesser(number);

    if (answer[GOOD] == NUM_DIGITS) {
        response = WIN_MSG;
        win();
    } else {
        if (answer[GOOD] > 0)
            response += std::to_string(answer[GOOD]) + GOOD;
        if (answer[REGULAR] > 0) {
            if (response.size() > 0) response += ", ";
            response += std::to_string(answer[REGULAR]) + REGULAR;
        }
        if (answer[BAD] > 0)
            response = std::to_string(answer[BAD]) + BAD;
    }
    return response;
}

void ThreadClient::win() {
    gameStats.addWinner();
    isFinished = true;
}

void ThreadClient::lose() {
    gameStats.addLoser();
    isFinished = true;
}
