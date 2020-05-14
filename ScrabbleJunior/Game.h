#ifndef SCRABBLE_JUNIOR_GAME_GAME_H
#define SCRABBLE_JUNIOR_GAME_GAME_H

#include "Player.h"
#include "../Board.h"
#include <string>
#include <vector>

class Game {
public:
    int numberOfPlayers, numOfTiles;
    std::vector<Player> players;
    Board board;
    std::vector<char> pool;
    std::string filename;

    Game();
    void getSettings();
    void getPlayers();
    void drawTiles();
    int getNumberOfPlayers();
    void coverTiles();                                 // check choosen player's tiles for invalid  position (if tile and letter in position are the same)
                                                       // put tile in position and change colour to red

    void controlBoard();
    char popLetter(int index);
    void showPool();
    void showPlayersTiles();
    void startGame();

};


#endif //#ifndef SCRABBLE_JUNIOR_GAME_GAME_H