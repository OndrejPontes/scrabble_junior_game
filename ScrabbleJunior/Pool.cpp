#include "Pool.h"

char Pool::popLetter(int index) {
    char result;
    result = letters[index];
    letters.erase(letters.begin() + index);
    return result;
}

int Pool::size() {
    return letters.size();
}
