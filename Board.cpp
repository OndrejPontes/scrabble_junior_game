#include "Board.h"
#include <windows.h>
#include <iostream>
#include <iterator>
#include <fstream>
#include <sstream>

using namespace std;

Board::Board(int x, int y) {
    vector<Tile> tiles;
    for (int i = 0; i < x; i++) {
        tiles = {};
        for (int j = 0; j < y; j++) {
            tiles.emplace_back(' ');
        }
        plan.push_back(tiles);
    }
}

// This function handle a lot of checks if word that user is adding will fit the plan. For any question don't hesitate
// to contact me, because it is hard to explain just with small comment. However, I think it is wrote as simple as possible.
void Board::addWord(const Word &word, bool check) {
    int endX, endY, counter;
    // Setup position of last character of word
    if (word.direction == Direction::V) {
        endX = word.x + (int) word.value.size();
        endY = word.y + 1;
    } else {
        endX = word.x + 1;
        endY = word.y + (int) word.value.size();
    }

    if (check) {
        // This awful condition check if there is a character before or after, start or end of the word. If so we cannot
        // add that word in board and error is thrown.
        if (
                (word.direction == Direction::V && (
                        (word.x > 0 && !plan[word.x - 1][word.y].isEmpty()) ||
                        (endX < plan.size() && !plan[endX][word.y].isEmpty())
                )) || (word.direction == Direction::H && (
                        (word.y > 0 && !plan[word.x][word.y - 1].isEmpty()) ||
                        (endY < plan[0].size() && !plan[word.x][endY].isEmpty())
                )))
            throw logic_error("This word cannot be added due to it's edge are touching others words.");

        // This horrible thing check if there are any characters next to currently added word. If so, there has to be
        // a character on place where we want to add a word.
        if (word.direction == Direction::H) {
            if (word.x - 1 >= 0) {
                for (int i = word.y; i < word.y + word.value.size(); i++) {
                    if (!plan[word.x - 1][i].isEmpty() && plan[word.x][i].isEmpty())
                        throw logic_error(
                                "This word cannot be added due to it's edge are touching others words.");
                }
            }
            if (word.x + 1 < plan.size()) {
                for (int i = word.y; i < word.y + word.value.size(); i++)
                    if (!plan[word.x + 1][i].isEmpty() && plan[word.x][i].isEmpty())
                        throw logic_error("This word cannot be added due to it's edge are touching others words.");
            }
        } else {
            if (word.y - 1 >= 0) {
                for (int i = word.x; i < word.x + word.value.size(); i++)
                    if (!plan[i][word.y - 1].isEmpty() && plan[i][word.y].isEmpty())
                        throw logic_error("This word cannot be added due to it's edge are touching others words.");
            }
            if (word.y + 1 < plan[0].size()) {
                for (int i = word.x; i < word.x + word.value.size(); i++)
                    if (!plan[i][word.y + 1].isEmpty() && plan[i][word.y].isEmpty())
                        throw logic_error("This word cannot be added due to it's edge are touching others words.");
            }
        }
    }

    // Check intersect with other words
    counter = 0;
    for (int i = word.x; i < endX; i++) {
        for (int j = word.y; j < endY; j++) {
            if (!plan[i][j].isEmpty() && plan[i][j].letter != word.value[counter])
                throw logic_error("The word you are entering cannot be entered due it do not match with "
                                  "letters already at board.");
            counter++;
        }
    }

    // Enter word into board
    counter = 0;
    for (int i = word.x; i < endX; i++) {
        for (int j = word.y; j < endY; j++) {
            plan[i][j].letter = word.value[counter];
            counter++;
        }
    }

    wordsCount++;
}

void Board::coverTile(int x, int y) {
    plan[x][y].isFree = false;
}

// This is function for printing game board and also returning a string of current game board, that is added to txt file
// when we are creating board.
string Board::print() {
    COORD coord;
    stringstream ss;

    for (int i = 0; i < plan.size() + 1; i++) {
        coord.X = i;
        if (i == 1) {
            ss << "===";
            for (int j = 0; j < plan[0].size() + 1; j++)
                ss << "==";
            ss << endl;
        }
        for (int j = 0; j < plan[0].size() + 1; j++) {
            coord.Y = j;
            if (i == 0 && j == 0) {
                cout << "  ";
                ss << "  ||";
            } else if (i == 0) {
                cout << char(96 + j) << " ";
                ss << char(96 + j) << (j == plan[0].size() ? "" : " ");
            } else if (j == 0) {
                cout << char(64 + i) << " ";
                ss << char(64 + i) << " ||";
            } else {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), plan[i - 1][j - 1].isFree ? 240 : 244);
                cout << plan[i - 1][j - 1].letter << (j == plan[0].size() ? "" : " ");
                ss << plan[i - 1][j - 1].letter << (j == plan[0].size() ? "" : " ");
            }
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        }
        cout << endl;
        ss << "||" << endl;
    }
    cout << endl;

    for (int j = 0; j < plan[0].size() + 3; j++)
        ss << (j == 0 ? "=" : "==");

    return ss.str();
}

// Function return height of plan
int Board::getDimensionX() {
    return plan.size();
}

// Function return width of plan
int Board::getDimensionY() {
    return plan[0].size();
}

// Static function used to load board from file created by board builder.
Board Board::loadFromFile(const string &filename) {
    ifstream file("./data/" + filename + ".txt");
    string str;
    vector<string> parsed;
    Board board;

    if (file) {
        getline(file, str);
        istringstream iss(str);
        parsed = {
                istream_iterator<string>(iss), {}
        };
        board = Board(stoi(parsed[0]), stoi(parsed[2]));

        while (getline(file, str) && !str.empty()) {
            board.addWord(Word::create(str), false);
        }
        file.close();
    } else {
        throw logic_error("File: ./data/ " + filename + ".txt wasn't found");

    }
    return board;
}

char Board::getTile(int x, int y) {
    return plan[x][y].letter;
}

// Returning default pool contains all letters on board
std::vector<char> Board::getDefaultPool() {
    vector<char> defaultPool;

    for (auto &row : plan)
        for (auto &tile : row)
            if (!tile.isEmpty())
                defaultPool.push_back(tile.letter);

    return defaultPool;
}

int Board::getWordCount() {
    return wordsCount;
}

int Board::getNumberOfCoveredWords() {
    int counter = 0;

    // Counting covered words
    for (int i = 0; i < plan.size(); i++) {
        for (int j = 0; j < plan[0].size(); j++) {
            if (!plan[i][j].isFree && (
                    (j == plan[0].size() - 1 && !plan[i][j - 1].isFree) ||
                    (j != 0) && !plan[i][j - 1].isFree && plan[i][j + 1].isEmpty() ||
                    (i == plan.size() - 1 && !plan[i - 1][j].isFree) ||
                    (i != 0) && !plan[i - 1][j].isFree && plan[i + 1][j].isEmpty()
            ))
                counter++;
        }
    }

    return counter;
}

// This function return number of words covered for last turn
int Board::getNumberOfLatestCoveredWords() {
    int latestNumberOfCoveredWords = getNumberOfCoveredWords();
    int result = latestNumberOfCoveredWords - coveredWords;
    coveredWords = latestNumberOfCoveredWords;
    return result;
}

bool Board::isAlreadyCovered(int x, int y) {
    return !plan[x][y].isFree;
}

// Get all characters that are possible to cover in the current turn
std::vector<Tile> Board::getAvailableLetters() {
    vector<Tile> result;

    for (int i = 0; i < plan.size(); ++i) {
        for (int j = 0; j < plan[0].size(); ++j) {
            Tile a = plan[i][j];
            if (!plan[i][j].isEmpty() && plan[i][j].isFree && (
                    (j == 0 && !plan[i][j + 1].isEmpty()) ||
                    (j == plan[0].size() - 1 && !plan[i][j - 1].isFree) ||
                    (j != 0 && j != plan[0].size() - 1 && (
                            !plan[i][j - 1].isFree ||
                            plan[i][j - 1].isEmpty() && !plan[i][j + 1].isEmpty() && plan[i][j + 1].isFree
                    )) ||
                    (i == 0 && !plan[i + 1][j].isEmpty()) ||
                    (i == plan.size() - 1 && !plan[i - 1][j].isFree) ||
                    (i != 0 && i != plan.size() - 1 && (
                            !plan[i - 1][j].isFree ||
                            plan[i - 1][j].isEmpty() && !plan[i + 1][j].isEmpty() && plan[i + 1][j].isFree
                    ))
            ))
                result.emplace_back(plan[i][j].letter, i, j);
        }
    }

    return result;
}

bool Tile::isEmpty() {
    return letter == ' ';
}