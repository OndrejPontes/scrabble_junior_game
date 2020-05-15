#include "Game.h"

using namespace std;

#include <iostream>
#include <sstream>
#include <iterator>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

void Game::startGame() {
    // Setup everything
    getPlayers();
    loadBoard();
    board.print();
    preparePool();
    prepareTilesForPlayers();

    // TODO: vo funcii coverTile: hrac vyberie tile, ktory chce zakrit vymaze sa mu z jeho poolu
    // TREBA dorobit aktualizovanie hracovho poolu po tom ako zakryje policko
    // Start playing
    do {
        players[activePlayerIndex].printLetters();
        coverTiles();
        activePlayerIndex = (activePlayerIndex + 1) % players.size();
    } while (gameDoesntHaveWinner());
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
    int totalScore = 0;

    for (auto player : players) {
        totalScore = +player.getScore();
    }

    return totalScore < board.getWordCount() && pool.size() != 0;

}

void Game::coverTiles() {

    // Update user score
    players[activePlayerIndex].increaseScore(board.getNumberOfLatestCoveredWords());
}


