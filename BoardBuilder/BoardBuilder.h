#ifndef SCRABBLE_JUNIOR_GAME_BOARDBUILDER_H
#define SCRABBLE_JUNIOR_GAME_BOARDBUILDER_H

#include "string"
#include "vector"

class BoardBuilder {
    int dimension_x;
    int dimension_y;
    char board[20][20];
    std::vector<std::string> words;
    bool shouldIKeepGoing = true;
private:
    void getSize();
    std::string getWord();
    std::string getNameOfFileWhereToSaveBoard();
    bool canWordBeAddedToBoard(std::string);
    void addWordToBoard(std::string);
    void printBoard();
    void saveBoard(std::string);
    void loadWords();
    int whatShouldIDo();

public:
    void startBuilding();
};


#endif //SCRABBLE_JUNIOR_GAME_BOARDBUILDER_H
