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

    bool isEmpty();
};

class Board {
private:
    std::vector<std::vector<Tile>> plan;
    int wordsCount = 0;

public:
    Board() = default;

    Board(int x, int y);

    std::string print();

    void addWord(const Word &word, bool check = true);

    void takeTile(int x, int y);

    int getDimensionX();

    int getDimensionY();

    char getTile(int x, int y);

    std::vector<char> getDefaultPool();

    static Board loadFromFile(const std::string &filename);

    int getWordCount();

    int getNumberOfCoveredWords();
};

#endif //SCRABBLE_JUNIOR_GAME_BOARD_H
