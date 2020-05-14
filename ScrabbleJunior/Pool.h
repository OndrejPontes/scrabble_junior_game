#ifndef SCRABBLE_JUNIOR_GAME_POOL_H
#define SCRABBLE_JUNIOR_GAME_POOL_H


#include <utility>
#include <vector>

class Pool {
private:
    std::vector<char> letters;
public:
    Pool(std::vector<char> letters) : letters(std::move(letters)) {}

    char popLetter(int index);

    int size();
};


#endif //SCRABBLE_JUNIOR_GAME_POOL_H
