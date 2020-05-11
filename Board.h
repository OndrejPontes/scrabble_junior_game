#ifndef SCRABBLE_JUNIOR_GAME_BOARD_H
#define SCRABBLE_JUNIOR_GAME_BOARD_H

#include <string>
#include <utility>
#include "vector"

struct Tile {
    char letter;
    bool isFree = true;

    explicit Tile(char letter) : letter(letter) {}
};

enum class Direction {V, H};

struct Word {
    std::string value;
    Direction direction;
    int x;
    int y;
    Word(std::string value, Direction direction, int x, int y): value{std::move(value)}, direction{direction}, x{x}, y{y} {}
};

class Board {
private:
    std::vector<std::vector<Tile>> plan;

public:
    Board() = default;
    Board(int x, int y);

    void print();
    void addWord(const Word&);
    void takeTile(int x, int y);
    int getDimensionX();
    int getDimensionY();
};

#endif //SCRABBLE_JUNIOR_GAME_BOARD_H
