#ifndef SCRABBLE_JUNIOR_GAME_SCRABBLEJUNIOR_H
#define SCRABBLE_JUNIOR_GAME_SCRABBLEJUNIOR_H
#include "struct.h"
#include "string"
#include "vector"




//class Player for each player
class Player {
public:
    std::string name;
    std::vector<char> letters;                               // with 7 tiles
    int score;

    Player();
    std::vector<int> drawTiles(std::vector<char> pool);          // draw tiles from pool and returns vec<int> with indexs of tiles
    std::vector<char> updateTiles();                             // check if player has 7 tiles,after his turn it will update #ofHisTiles
    std::vector<char> playTurn();                                // choose  2 tiles to play and position
                                                                 // check for invalid tiles (if player has choosen tiles in hand)
    int  updateScore();                                                                                            
    void showPlayersTiles();                                     // TODO: not sure if input must be playerPool
    void showPlayersScore();
    bool doWantPlayTurn();                                       // if player doesn't want play, change his 2 tiles from pool


    void getName();
};

// class attributes of board e.g. pool, scoring chips
class Board {

private:
     vector<Tile>
public:
    std::vector<char> pool;                  // with 101  tiles
    int scoringChips;                              // 44 chips

    Board();
    void loadPlan(string file);
    char popLetter(int index);

    void setPool(std::vector<char>& pool);
    void printBoard();                                 // print board from board file.txt
    void controlBoard();                                // after coverTiles, check if there is a completed word and print board again
    
};

// class with all functionalities
class Game {
public:
    int numberOfPlayers;
    std::vector<Player> players;
    Board board= Board();
    //Game();
    void drawTiles();
    int getNumberOfPlayers();
    void coverTiles();                                 // check choosen player's tiles for invalid  position (if tile and letter in position are the same)
                                                       // put tile in position and change colour to red
    


    void startGame();

};
#endif //SCRABBLE_JUNIOR_GAME_SCRABBLEJUNIOR_H
