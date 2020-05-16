#ifndef SCRABBLE_JUNIOR_GAME_GAME_H
#define SCRABBLE_JUNIOR_GAME_GAME_H

#include "Player.h"
#include "string"
#include "vector"
#include <windows.h>

#include "../Board.h"
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

    std::vector<Tile> getAvailableTilesForUser();

    Tile getTile();

    void changeLetters(int cover);

    void clean();

    void printDefaultInformation();

    void announceWinner();

public:
    void startGame();
};

#endif //#ifndef SCRABBLE_JUNIOR_GAME_GAME_H