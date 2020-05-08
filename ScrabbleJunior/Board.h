
#include "string"
#include "vector"

struct Tile {
    char letter;
    std::string colour;
};

class Board {

private:
    std::vector<std::vector<Tile>> tiles;
public:
    std::vector<char> pool;                  // with 101  tiles
    int scoringChips;                              // 44 chips

    Board();
    void showPool();
    void loadPlan(std::string file);
    char popLetter(int index);

    void setPool(std::vector<char>& pool);
    void printBoard();                                 // print board from board file.txt
    void controlBoard();                                // after coverTiles, check if there is a completed word and print board again

};

