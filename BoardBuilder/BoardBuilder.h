#ifndef SCRABBLE_JUNIOR_GAME_BOARDBUILDER_H
#define SCRABBLE_JUNIOR_GAME_BOARDBUILDER_H

#include "string"
#include "vector"

class BoardBuilder {
    int dimension_x = 20;
    int dimension_y = 20;
    char board[20][20];
    std::vector<std::string> words;
    bool shouldIKeepGoing = true;
    std::vector<std::string> plan;
private:
    void getSize();
    void loadWords();
    void printBoard();
    std::string getWord();
    std::string getNameOfFileWhereToSaveBoard();
    bool canWordBeAddedToBoard(std::string);
    void addWordToBoard(std::string);
    void saveBoard(std::string);
    int whatShouldIDo();

public:
    void startBuilding();
};


#endif //SCRABBLE_JUNIOR_GAME_BOARDBUILDER_H
