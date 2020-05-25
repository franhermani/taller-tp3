#ifndef GAME_STATS_H
#define GAME_STATS_H

#include <atomic>

class GameStats {
    std::atomic<int> numWinners;
    std::atomic<int> numLosers;

public:
    // Constructor
    GameStats();

    // Constructor y asignacion por copia deshabilitados
    GameStats(const GameStats&) = delete;
    GameStats& operator=(const GameStats&) = delete;

    // Incrementa en uno la cantidad de ganadores
    void addWinner();

    // Incrementa en uno la cantidad de perdedores
    void addLoser();

    // Obtiene la cantidad de ganadores
    const int getWinners() const;

    // Obtiene la cantidad de perdedores
    const int getLosers() const;
};

#endif // GAME_STATS_H
