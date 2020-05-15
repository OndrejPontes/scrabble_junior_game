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

void Board::takeTile(int x, int y) {
    plan[x][y].isFree = false;
}

string Board::print() {
    COORD coord;
    stringstream ss;

    for (int i = 0; i < plan.size() + 1; i++) {
        coord.X = i;
        if (i == 1) {
            ss << "====";
            for (int j = 0; j < plan[0].size() + 1; j++)
                ss << "=";
            ss << endl;
        }
        for (int j = 0; j < plan[0].size() + 1; j++) {
            coord.Y = j;
            if (i == 0 && j == 0) {
                cout << ' ';
                ss << " ||";
            } else if (i == 0) {
                cout << char(96 + j);
                ss << char(96 + j);
            } else if (j == 0) {
                cout << char(64 + i);
                ss << char(64 + i) << "||";
            } else {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), plan[i - 1][j - 1].isFree ? 240 : 244);
                cout << plan[i - 1][j - 1].letter;
                ss << plan[i - 1][j - 1].letter;
            }
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        }
        cout << endl;
        ss << "||" << endl;
    }
    cout << endl;

    for (int j = 0; j < plan[0].size() + 5; j++)
        ss << "=";

    return ss.str();
}

int Board::getDimensionX() {
    return plan.size();
}

int Board::getDimensionY() {
    return plan[0].size();
}

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

    // Counting covered horizontal words
    for (auto &row : plan) {
        for (int j = plan[0].size() - 1; j > 0; --j) {
            if ((j == plan[0].size() - 1 && !row[j].isFree && !row[j - 1].isFree) ||
                (row[j + 1].isEmpty() && !row[j].isFree && !row[j - 1].isFree))
                counter++;
        }
    }

    // Counting covered vertical words
    for (int i = 0; i < plan[0].size(); i++) {
        for (int j = plan.size() - 1; j > 0; --j) {
            if ((j == plan.size() - 1 && !plan[j][i].isFree && !plan[j - 1][i].isFree) ||
                (plan[j + 1][i].isEmpty() && !plan[j][i].isFree && !plan[j - 1][i].isFree))
                counter++;
        }
    }

    return counter;
}

bool Tile::isEmpty() {
    return letter == ' ';
}
