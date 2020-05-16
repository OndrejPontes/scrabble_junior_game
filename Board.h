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
    int x = 0;
    int y = 0;

    explicit Tile(char letter) : letter(letter) {};

    Tile (char letter, int x, int y) : letter(letter), x(x), y(y) {};

    bool isEmpty();
};

class Board {
private:
    std::vector<std::vector<Tile>> plan;
    int wordsCount = 0;
    int coveredWords = 0;

    int getNumberOfCoveredWords();

public:
    Board() = default;

    Board(int x, int y);

    std::string print();

    void addWord(const Word &word, bool check = true);

    void coverTile(int x, int y);

    int getDimensionX();

    int getDimensionY();

    char getTile(int x, int y);

    std::vector<char> getDefaultPool();

    static Board loadFromFile(const std::string &filename);

    int getWordCount();

    int getNumberOfLatestCoveredWords();

    bool isAlreadyCovered(int x, int y);

    std::vector<Tile> getAvailableLetters();
};

#endif //SCRABBLE_JUNIOR_GAME_BOARD_H