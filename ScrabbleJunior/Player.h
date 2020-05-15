#ifndef SCRABBLE_JUNIOR_GAME_PLAYER_H
#define SCRABBLE_JUNIOR_GAME_PLAYER_H

#include "string"
#include "vector"

class Player {
private:
    std::string name;
    std::vector<char> letters;
    int score = 0;

public:
    Player(int i);

    std::string getName();

    void addLetter(const char &letter);

    void removeLetter(char letter);

    int getScore();

    void increaseScore(int toAdd);

    void printLetters();

    const std::vector<char> &getLetters() const;

    
};

#endif //SCRABBLE_JUNIOR_GAME_PLAYER_H