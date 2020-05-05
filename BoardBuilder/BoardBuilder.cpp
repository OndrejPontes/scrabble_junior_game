#include "BoardBuilder.h"

using namespace std;

#include <iostream>
#include <fstream>


void BoardBuilder::startBuilding() {
    string word;

    getSize();
    loadWords();

//    while (shouldIKeepGoing) {
    printBoard();
//        switch (whatShouldIDo()) {
//            case 0:
//                saveBoard(getNameOfFileWhereToSaveBoard());
//                break;
//            case 1:
//                word = getWord();
//                if (canWordBeAddedToBoard(word)) {
//                    addWordToBoard(word);
//                }
//                break;
//            default:
//                shouldIKeepGoing = false;
//        }
//    }
}

// Asking user for size of the board
void BoardBuilder::getSize() {
    string input, x, y;
    bool inputIsValid;
    cout << "Welcome in Board Builder console app." << endl;
    do {
        // I am suggesting that input is valid on the start of every loop
        inputIsValid = true;
        cout << "Please enter size of board (example: 5x8): ";
        getline(cin, input);
        auto delimiter_position = input.find("x"); // Looking for 'x' to know how to split input
        // In the case 'x' wasn't find error message will be shown and loop will start again
        if (delimiter_position == string::npos) {
            cout << "Input is invalid. Use 'x' as divider of two numbers." << endl;
            inputIsValid = false;
            continue;
        }
        // Dividing user input to two parts by position of 'x'
        x = input.substr(0, delimiter_position);
        y = input.substr(delimiter_position + 1, input.length());

        // Converting two find strings into integer dimensions, whenever some error will occur there is proper reaction
        try {
            dimension_x = stoi(x);
            dimension_y = stoi(y);
        } catch (invalid_argument) {
            cout << "Input is invalid. There can't be any other character between numbers except 'x'" << endl;
            inputIsValid = false;
            continue;
        } catch (out_of_range) {
            cout << "Input is invalid. Numbers has to be in range from 0 to 20." << endl;
            inputIsValid = false;
            continue;
        }
        if (dimension_x < 0 || dimension_x > 20 || dimension_y < 0 || dimension_y > 20) {
            cout << "Input is invalid. Numbers has to be in range from 0 to 20." << endl;
            inputIsValid = false;
        }
    } while (!inputIsValid);
    plan.push_back(to_string(dimension_x) + " x " + to_string(dimension_y));
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
    } else {
        cout << "File WORDS.TXT wan't found";
    }
}

// Printing actual board
void BoardBuilder::printBoard() { // TODO: add colors and clear command line on start
    for (int x = 0; x < dimension_x + 1; x++) {
        for (int y = 0; y < dimension_y + 1; y++) {
            if (x == 0 && y == 0)
                cout << " ";
            else if (x == 0)
                cout << char(96 + y);
            else if (y == 0)
                cout << char(64 + x);
            else
                cout << board[x-1][y-1];
        }
        cout << endl;
    }
}
