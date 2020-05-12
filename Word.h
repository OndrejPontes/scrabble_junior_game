#ifndef SCRABBLE_JUNIOR_GAME_WORD_H
#define SCRABBLE_JUNIOR_GAME_WORD_H

#include <string>

enum class Direction {
    V, H
};

struct Word {
    std::string value;
    Direction direction = Direction::H;
    int x = 20;
    int y = 20;

    Word() = default;

    Word(std::string value, Direction direction, int x, int y) : value{std::move(value)}, direction{direction}, x{x},
                                                                 y{y} {}

    std::string toString();

    static Word create(std::string);
};

#endif //SCRABBLE_JUNIOR_GAME_WORD_H