#ifndef SCRABBLE_JUNIOR_GAME_BOARDBUILDER_H
#define SCRABBLE_JUNIOR_GAME_BOARDBUILDER_H

#include <string>
#include <vector>
#include "../Board.h"

class BoardBuilder {
    Board board;
    std::vector<std::string> words;
    bool shouldIKeepGoing = true;
    std::vector<std::string> plan;
private:
    void getSize();

    void loadWords();

    static std::string getFileName();

    void addWord();

    void saveBoard(const std::string &name);

    static int whatShouldIDo();

    Word createWord();

public:
    void startBuilding();
};


#endif //SCRABBLE_JUNIOR_GAME_BOARDBUILDER_H