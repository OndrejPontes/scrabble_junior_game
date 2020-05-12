#ifndef SCRABBLE_JUNIOR_GAME_BOARD_H
#define SCRABBLE_JUNIOR_GAME_BOARD_H

#include <string>
#include <utility>
#include <ostream>
#include <vector>
#include "Word.h"

struct Tile {
    char letter;
    bool isFree = true;

    explicit Tile(char letter) : letter(letter) {}
};

class Board {
private:
    std::vector<std::vector<Tile>> plan;

public:
    Board() = default;

    Board(int x, int y);

    void print();

    void addWord(const Word &);

    void takeTile(int x, int y);

    int getDimensionX();

    int getDimensionY();

    static Board loadFromFile(const std::string &filename);
};

#endif //SCRABBLE_JUNIOR_GAME_BOARD_H
