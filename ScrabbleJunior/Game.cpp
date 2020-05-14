#include "Game.h"

using namespace std;

#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>

void Game::startGame() {
    // Setup everything
    getPlayers();
    loadBoard();
    preparePool();
    prepareTilesForPlayers();

    // Start playing
//    do {
//
//    } while(gameDoesntHaveWinner());
//
//    drawTiles();
//    showPool();        // show pool after draw
//    Board::loadFromFile("test").print();
//    coverTiles();

}

void Game::getPlayers() {
    int numberOfPlayers = getNumberOfPlayers();
    for (int i = 0; i < numberOfPlayers; i++) {
        players.emplace_back(i);
    }
    cout << "Our players are: ";
    for (int i = 0; i < numberOfPlayers; i++) {
        cout << players[i].getName() << (i == numberOfPlayers - 1 ? " " : ", ");
    }
    cout << endl << endl;
}

int Game::getNumberOfPlayers() {
    int numberOfPlayers = 0;
    string input;

    while (numberOfPlayers < 2 || numberOfPlayers > 4) {
        cout << "Enter number of players(2-4): ";
        getline(cin, input);

        try {
            numberOfPlayers = stoi(input);
        } catch (const invalid_argument &) {
            cout << "Input is invalid. There can't be any other character then number" << endl;
        } catch (const out_of_range &) {
            cout << "Input is invalid. Number has to be in range 2-4." << endl;
        }

        if (numberOfPlayers < 2 || numberOfPlayers > 4)
            cout << "Input is invalid. Number has to be in range 2-4." << endl;
    }

    return numberOfPlayers;
}

void Game::loadBoard() {
    string input;
    bool isLoaded;

    do {
        cout << "Enter name of txt file in ./data/ that contains information about board without extension." << endl;
        cout << "File name: ";
        getline(cin, input);

        try {
            board = Board::loadFromFile(input);
            isLoaded = true;
        } catch (const logic_error &error) {
            cout << error.what() << endl;
            isLoaded = false;
        }

    } while (!isLoaded);
}

void Game::preparePool() {
    string input;
    int additionalTiles;
    vector<char> defaultPool = board.getDefaultPool();

    cout << "Your default pool has " << to_string(defaultPool.size()) << " tiles, how many do you want to add, to make "
         << "it more difficult ?" << endl;
    cout << "Number of additional tiles: ";
    getline(cin, input);

    try {
        additionalTiles = stoi(input);
    } catch (const invalid_argument &) {
        cout << "Input is invalid. There can't be any other character then number" << endl;
    } catch (const out_of_range &) {
        cout << "Input is invalid. Number has to be in range of Integer." << endl;
    }

    // Adding random tiles according to C++ 11 standards
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(65, 90);
    vector<int> v;
    vector<int> c;
    for (int i = 0; i < additionalTiles; ++i) {
        int x = dist(mt);
        v.push_back(dist(mt));
        c.push_back(i);
        defaultPool.push_back((char) x);
    }

    pool = defaultPool;
}

void Game::prepareTilesForPlayers() {
    // Adding random letters to users according to C++ 11 standards
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist;

    for (auto &player : players) {
        for (int i = 0; i < 7; i++) {
            dist = uniform_int_distribution(0, pool.size() - 1);
            player.addLetter(pool.popLetter(dist(mt)));
        }
    }
}

bool Game::gameDoesntHaveWinner() {
    throw logic_error("Not implemented"); // TODO: finish this
}

// Od tialto som s tym nic nerobil
//
//void Game::coverTiles() {
//    int posX, posY;
//    vector<string> parsed;
//    string line;
//    bool keepGoing = true;
//    cout
//            << "Enter tile that you want to cover in format  'Ak T'. The first pair represents the coordinates where you want to place the tile."
//               "Second parameter is your tile." << endl;
//    cin.ignore();
//    // while user's input is not correct, user must enter tile again
//    while (keepGoing) {
//        cout << "\nYour tile: ";
//
//        getline(cin, line);
//        istringstream iss(line);
//        parsed = {
//                istream_iterator<string>(iss), {}
//        };
//        posX = (int) parsed[0][0] - 64;
//        posY = (int) parsed[0][1] - 96;
//        if ((parsed.size() == 2) && (parsed[0].size() == 2) && (posX >= 1) && (posX <= board.getDimensionX()) &&
//            (posY >= 1) && (posY <= board.getDimensionY())) {
//
//            if (parsed[1][0] != board.getTile((int) parsed[0][0], (int) parsed[0][1]) &&
//                find(players[0].letters.begin(), players[0].letters.end(), parsed[1][0])
//                == players[0].letters.end()) {
//                cout << "You can't cover this tile!";
//            } else {
//                board.takeTile((int) parsed[0][0], (int) parsed[0][1]);
//                keepGoing = false;
//            }
//        } else {
//            cout << " Enter excatly 2 parameters and check if parameters  do not exceeds dimensions of board! ";
//        }
//
//    }
//}
//
//void Game::drawTiles() {
//    int r, numOfPlayersTile = 7;
//
//    srand(time(NULL));
//    for (int i = 0; i < players.size(); i++) {
//        for (int j = 0; j < numOfPlayersTile; j++) {
//            r = rand() % pool.size();
//            players[i].letters.push_back(popLetter(r));
//        }
//    }
//    showPlayersTiles();
//
//
//}
//
//// Initialization of random letters in the pool
//Game::Game() {
//    getSettings();
//    char letter;
//    srand(time(NULL));                            // to make initialization random using time seed
//    for (int i = 0; i < numOfTiles; i++) {
//        letter = 'a' + rand() % 26;            // Convert to a character from a-z
//        pool.push_back(letter);
//    }
//}
//
//void Game::getSettings() {// initialization parameters of game
//    int input;
//    bool keepGoing = true;
//    cout << "\t\tWELCOME TO SCRABBLE GAME !\nFirst of all, let's go through the game settings.\n\n";
//    while (keepGoing) {
//        cout << "How many tiles do you want to play with(Minimum value for two players is 14): ";
//        cin >> input;
//        if (cin.fail()) {
//            cin.clear();
//            cin.ignore(256, '\n');
//            cout << "Enter valid value!\n";
//        } else if (input >= 14) {
//            keepGoing = false;
//            numOfTiles = input;
//        }
//    }
//
//}
//
//void Game::showPool() {
//    string input;
//    // with 101 letters in pool, it might be unclear in terminal
//    cout << "\nIf you want to see pool, press 'y': ";
//    cin >> input;
//    if (input == "y") {
//        cout << "OUR POOL IS: \n";
//        for (int k = 0; k < pool.size(); k++)
//            cout << pool[k] << " ";
//        cout << "\nNumber of letters in pool: " << pool.size() << "\n";
//
//    }
//
//}
//
//void Game::showPlayersTiles() {
//    cout << endl << " PLAYER'S TILES: " << endl;
//    for (int temp = 0; temp < players.size(); temp++) {
//        cout << "Player " << temp << ".: ";
//        for (int l = 0; l < players[temp].letters.size(); l++) {
//            cout << players[temp].letters[l] << " ";
//
//        }
//        cout << endl;
//    }
//}