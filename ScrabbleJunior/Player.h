
#include "string"
#include "vector"

class Player {
public:
    std::string name;
    std::vector<char> letters;                               // with 7 tiles
    int score;

    Player();
    std::vector<char> updateTiles();                             // check if player has 7 tiles,after his turn it will update #ofHisTiles
    std::vector<char> playTurn();                                // choose  2 tiles to play and position
                                                                 // check for invalid tiles (if player has choosen tiles in hand)
    int  updateScore();
    void showPlayersTiles();                                     // TODO: not sure if input must be playerPool
    void showPlayersScore();
    bool doWantPlayTurn();                                       // if player doesn't want play, change his 2 tiles from pool


    void getName();
};

