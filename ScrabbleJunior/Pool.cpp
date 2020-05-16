#include "Pool.h"
#include <random>

using namespace std;

char Pool::popLetter() {
    char result;
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(0, letters.size() - 1);
    int index = dist(mt);
    result = letters[index];
    letters.erase(letters.begin() + index);
    return result;
}

int Pool::size() {
    return letters.size();
}

void Pool::addLetter(char letter) {
    letters.emplace_back(letter);
}