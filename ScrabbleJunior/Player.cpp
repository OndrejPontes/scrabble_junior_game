#include "Player.h"

using namespace std;

#include <iostream>

Player::Player(int i) {
    cout << to_string(i + 1) << ". player name: ";
    getline(cin, name);
}

std::string Player::getName() {
    return name;
}

void Player::addLetter(const char &letter) {
    letters.push_back(letter);
}

void Player::removeLetter(char letter) {
    auto it = find(letters.begin(), letters.end(), letter);
    if (it != letters.end())
        letters.erase(it);
    else
        throw logic_error("Letter '" + to_string(letter) + "' that you want to delete for player " + name +
                          " is not in his/her letters.");
}

int Player::getScore() {
    return score;
}

void Player::increaseScore(int toAdd) {
    score += toAdd;
}

void Player::printLetters() {
    cout << "Player " << name << " has these letters: ";
    for(auto &letter : letters)
        cout << letter << " ";
    cout << endl;
}

const std::vector<char> &Player::getLetters() const {
    return letters;
}


