#include "server_game_stats.h"

GameStats::GameStats() : numWinners(0), numLosers(0) {}

void GameStats::addWinner() {
    numWinners += 1;
}

void GameStats::addLoser() {
    numLosers += 1;
}

const int GameStats::getWinners() const {
    return numWinners;
}

const int GameStats::getLosers() const {
    return numLosers;
}
