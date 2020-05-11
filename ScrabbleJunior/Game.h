
#include "Player.h"
#include "Board.h"
#include "string"
#include "vector"

class Game {
public:
    int numberOfPlayers;
    std::vector<Player> players;
    Board board = Board();
    std::vector<char> pool;

    void getPlayers();
    void drawTiles();
    int getNumberOfPlayers();
    void coverTiles();                                 // check choosen player's tiles for invalid  position (if tile and letter in position are the same)
                                                       // put tile in position and change colour to red


    char popLetter(int index);
    void showPool();
    void startGame();

};
