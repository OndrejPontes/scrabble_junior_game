#include "BoardBuilder.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>

using namespace std;

void BoardBuilder::startBuilding() {
    getSize();
    loadWords();

    while (shouldIKeepGoing) {
        board.print();
        switch (whatShouldIDo()) {
            case 0:
                saveBoard(getNameOfFileWhereToSaveBoard());
                break;
            case 1:
                addWordToBoard();
                break;
            default:
                shouldIKeepGoing = false;
        }
    }
}

// Asking user for size of the board
void BoardBuilder::getSize() {
    string input;
    int x, y;
    bool inputIsValid;
    cout << "Welcome in Board Builder console app." << endl;
    do {
        // I am suggesting that input is valid on the start of every loop
        inputIsValid = true;
        cout << "Please enter size of board (example: 5x8): ";
        getline(cin, input);
        auto delimiter_position = input.find('x'); // Looking for 'x' to know how to split input
        // In the case 'x' wasn't find error message will be shown and loop will start again
        if (delimiter_position == string::npos) {
            cout << "Input is invalid. Use 'x' as divider of two numbers." << endl;
            inputIsValid = false;
            continue;
        }

        // Converting two find strings into integer dimensions, whenever some error will occur there is proper reaction
        try {
            x = stoi(input.substr(0, delimiter_position));
            y = stoi(input.substr(delimiter_position + 1, input.length()));
        } catch (const invalid_argument &) {
            cout << "Input is invalid. There can't be any other character between numbers except 'x'" << endl;
            inputIsValid = false;
            continue;
        } catch (const out_of_range &) {
            cout << "Input is invalid. Numbers has to be in range from 0 to 20." << endl;
            inputIsValid = false;
            continue;
        }
        if (x < 0 || x > 20 || y < 0 || y > 20) {
            cout << "Input is invalid. Numbers has to be in range from 0 to 20." << endl;
            inputIsValid = false;
        }
    } while (!inputIsValid);

    board = Board(x, y);
    plan.push_back(to_string(x) + " x " + to_string(y));
    // That's it, we set size of board
}

// Checking if file with words exists, loading data from WORDS.TXT file and saving it into words vector
void BoardBuilder::loadWords() {
    ifstream file("../BoardBuilder/data/WORDS.TXT"); // TODO: Ask if this have to be hardcoded here
    string str;
    if (file) {
        while (getline(file, str)) {
            words.push_back(str);
        }
        file.close();
    } else {
        cout << "File WORDS.TXT wasn't found";
    }
}

// Let user decide what he wants to do.
int BoardBuilder::whatShouldIDo() {
    string choice;
    do {
        cout << "If you want to save board press: 's'" << endl;
        cout << "If you want to add word press: 'a'" << endl;
        cout << "If you want to exit without saving press: 'x'" << endl;
        cout << "Your choice: ";

        getline(cin, choice);

        if (choice == "s")
            return 0;
        if (choice == "a")
            return 1;
        if (choice == "x")
            return -1;
        cout << endl << "You have to enter one of the options." << endl;
    } while (true);
}

std::string BoardBuilder::getNameOfFileWhereToSaveBoard() {
    string fileName;

    cout << "Enter name of file (without extension): ";
    getline(cin, fileName);

    return fileName;
}

void BoardBuilder::saveBoard(const string &name) {
    ofstream file(name + "txt");

    for (const auto &line : plan)
        file << line;

    file.close();
}

void BoardBuilder::addWordToBoard() {
    Word word;
    bool inputIsInvalid = false;

    cout << "Enter word that you want to add in this format: 'Ak H EGGS'. Where first parameter is pair indicate "
            "position of first letter of the word. Second parameter is 'V' - vertical or 'H' - horizontal which "
            "indicate direction of word and last parameter is the word itself." << endl;
    cout << "Your word: ";

    do {
        try {
            word = createWord();
            board.addWord(word);
            inputIsInvalid = false;
        } catch (const logic_error &error) {
            cout << error.what() << endl << "Try again: ";
            inputIsInvalid = true;
        }
    } while (inputIsInvalid);
}

Word BoardBuilder::createWord() {
    string input;
    vector<string> parsed;
    string value;
    Direction direction;

    // Getting input from user
    getline(cin, input);

    // Parsing input from user by whitespaces
    istringstream iss(input);
    parsed = {
            istream_iterator<string>(iss), {}
    };

    // Checking user entered 3 parameters
    if (parsed.size() != 3)
        throw logic_error("Enter exactly 3 parameters separated by whitespace.");

    // Checking if first parameter is position from right range
    if (parsed[0].size() != 2 ||
        !((int) parsed[0][1] >= (int) 'a' && (int) parsed[0][1] < (int) 'a' + board.getDimensionY() &&
          (int) parsed[0][0] >= (int) 'A' && (int) parsed[0][0] < (int) 'A' + board.getDimensionX()))
        throw logic_error("Word position is incorrect.");

    // Checking if second parameter is V or H
    if (parsed[1] != "V" && parsed[1] != "H")
        throw logic_error("Second parameter has to be 'V' or 'H'.");

    if (parsed[1][0] == 'V')
        direction = Direction::V;
    else
        direction = Direction::H;

    // Checking if last parameter is word that is in our dictionary
    value = parsed[2];
    for_each(value.begin(), value.end(), [](char &c) {
        c = (char) tolower(c);
    });
    if (find(words.begin(), words.end(), value) == words.end())
        throw logic_error("Word: " + parsed[2] + " is not in our list 'WORDS.TXT'.");

    for_each(value.begin(), value.end(), [](char &c) {
        c = (char) toupper(c);
    });

    return Word(value, direction, parsed[0][0] - 65, (int) parsed[0][1] - 97);
}
