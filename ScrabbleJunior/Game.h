#ifndef SCRABBLE_JUNIOR_GAME_GAME_H
#define SCRABBLE_JUNIOR_GAME_GAME_H

#include "Player.h"
#include "../Board.h"
#include "string"
#include "vector"
#include "Pool.h"

class Game {
private:
    std::vector<Player> players;
    Board board;
    Pool pool;
    int activePlayerIndex = 0;

    void getPlayers();

    void loadBoard();

    void preparePool();

    void prepareTilesForPlayers();

    bool gameDoesntHaveWinner();

    int getNumberOfPlayers();

    void coverTiles();

public:
    void startGame();
};

#endif //#ifndef SCRABBLE_JUNIOR_GAME_GAME_H