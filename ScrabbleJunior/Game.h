#ifndef SCRABBLE_JUNIOR_GAME_GAME_H
#define SCRABBLE_JUNIOR_GAME_GAME_H

#include "Player.h"
#include "../Board.h"
#include "string"
#include "vector"

class Game {
private:
    int numberOfPlayers, numOfTiles;
    std::vector<Player> players;
    Board board = Board();
    std::vector<char> pool;
    std::string filename;
    void getSettings();
    void getPlayers();
    void drawTiles();
    int getNumberOfPlayers();
    void coverTiles();                                 // check choosen player's tiles for invalid  position (if tile and letter in position are the same)
    void controlBoard();
    char popLetter(int index);
    void showPool();
    void showPlayersTiles();
public:
    void startGame();

    Game();
};

#endif //#ifndef SCRABBLE_JUNIOR_GAME_GAME_H