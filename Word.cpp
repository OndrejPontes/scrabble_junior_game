#include "Word.h"
#include <sstream>
#include <iterator>
#include <vector>

using namespace std;

// This string is in format that we are using for work in our txt files
string Word::toString() {
    string line;
    line = (char) (x + (int) 'A');
    line += (char) (y + (int) 'a');
    line += direction == Direction::V ? " V " : " H ";
    line += value;
    return line;
}

// This is light-way function of createWord in BoardBuilder class. This function should be used just for already verified input
Word Word::create(std::string input) {
    vector<string> parsed;
    istringstream iss(input);
    parsed = {istream_iterator<string>(iss), {}};

    return Word(parsed[2], parsed[1] == "V" ? Direction::V : Direction::H, (int) parsed[0][0] - (int) 'A',
                (int) parsed[0][1] - (int) 'a');
}


