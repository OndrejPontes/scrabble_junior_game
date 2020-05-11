#include "Board.h"
#include <windows.h>
#include <iostream>

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

void Board::addWord(const Word &word) {
    int endX, endY, counter = 0;
    // Setup position of last character of word
    if (word.direction == Direction::V) {
        endX = word.x + (int) word.value.size();
        endY = word.y + 1;
    } else {
        endX = word.x + 1;
        endY = word.y + (int) word.value.size();
    }

    // This awful condition check if there is a character before or after, start or end of the word. If so we cannot
    // add that word in board and error is thrown.
    if (
            (word.direction == Direction::V && (
                    (word.x > 0 && plan[word.x - 1][word.y].letter != ' ') ||
                    (endX < plan.size() && plan[endX][word.y].letter != ' ')
            )) || (word.direction == Direction::H && (
                    (word.y > 0 && plan[word.x][word.y - 1].letter != ' ') ||
                    (endY < plan[0].size() && plan[word.x][endY].letter != ' ')
            )))
        throw logic_error("This word cannot be added due to it's edge are touching others words.");

    // Check intersect with other words
    counter = 0;
    for (int i = word.x; i < endX; i++) {
        for (int j = word.y; j < endY; j++) {
            if (plan[i][j].letter != ' ' && plan[i][j].letter != word.value[counter])
                throw logic_error("The word you are entering cannot be entered due it do not match with "
                                  "letters already at board.");
            counter++;
        }
    }

    // Enter word into board
    for (int i = word.x; i < endX; i++) {
        for (int j = word.y; j < endY; j++) {
            plan[i][j].letter = word.value[counter];
            counter++;
        }
    }
}

void Board::takeTile(int x, int y) {
    plan[x][y].isFree = false;
}

void Board::print() {
    COORD coord;

    for (int i = 0; i < plan.size() + 1; i++) {
        coord.X = i;
        for (int j = 0; j < plan[0].size() + 1; j++) {
            coord.Y = j;
            if (i == 0 && j == 0)
                cout << ' ';
            else if (i == 0)
                cout << char(96 + j);
            else if (j == 0)
                cout << char(64 + i);
            else {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), plan[i - 1][j - 1].isFree ? 240 : 244);
                cout << plan[i - 1][j - 1].letter;
            }
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        }
        cout << endl;
    }
    cout << endl;
}

int Board::getDimensionX() {
    return plan.size();
}

int Board::getDimensionY() {
    return plan[0].size();
}
