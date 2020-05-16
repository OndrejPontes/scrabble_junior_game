#include "Game.h"

using namespace std;

#include <algorithm>
#include <iostream>
#include <iterator>
#include <random>
#include <string>
#include <vector>

void Game::startGame() {
    // Setup everything
    getPlayers();
    loadBoard();
    preparePool();
    prepareTilesForPlayers();

    // Start playing
    do {
        coverTiles();
        activePlayerIndex = (activePlayerIndex + 1) % players.size();
    } while (gameDoesntHaveWinner());

    announceWinner();
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

    cout << endl;
}

void Game::preparePool() {
    string input;
    int additionalTiles;
    vector<char> defaultPool = board.getDefaultPool();
    bool inputIsValid = false;

    cout << "Your default pool has " << to_string(defaultPool.size()) << " tiles, how many do you want to add, to make "
         << "it more difficult ?" << endl;
    do {
        cout << "Number of additional tiles: ";

        getline(cin, input);

        try {
            additionalTiles = stoi(input);
            inputIsValid = true;
        } catch (const invalid_argument &) {
            cout << "Input is invalid. There can't be any other character then number" << endl;
        } catch (const out_of_range &) {
            cout << "Input is invalid. Number has to be in range of Integer." << endl;
        }
    } while (!inputIsValid);

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
    for (auto &player : players) {
        for (int i = 0; i < 7; i++) {
            player.addLetter(pool.popLetter());
        }
    }
}

bool Game::gameDoesntHaveWinner() {
    int totalScore = 0;

    for (auto player : players) {
        totalScore += player.getScore();
    }

//    return totalScore < board.getWordCount() && pool.size() != 0;
    return totalScore < board.getWordCount();

}

void Game::coverTiles() {
    vector<string> parsed;
    string line;
    vector<Tile> tilesForCover = getAvailableTilesForUser();
    int tilesToCover = 2;
    bool enteredInvalidLetter = false;

    while (tilesToCover > 0 && !tilesForCover.empty()) {
        printDefaultInformation();
        if (enteredInvalidLetter)
            cout << "You entered position of tile that you don't have in your letters or is empty. Try again." << endl
                 << endl;

        cout << players[activePlayerIndex].getName() << " enter position of "
             << (2 - tilesToCover == 0 ? "first" : "second") << " tile that you want to cover in format 'Ak'" << endl;
        Tile userTile = getTile();

        for (auto &tile : tilesForCover) {
            if (tile.letter == userTile.letter && tile.x == userTile.x && tile.y == userTile.y) {
                players[activePlayerIndex].removeLetter(tile.letter);
                board.coverTile(tile.x, tile.y);
                tilesForCover = getAvailableTilesForUser();
                tilesToCover--;
                enteredInvalidLetter = false;
                break;
            } else {
                enteredInvalidLetter = true;
            }
        }
    }

    if (tilesToCover > 0)
        changeLetters(tilesToCover);

    if (pool.size() > 0)
        for (int i = 0; i < 7 - players[activePlayerIndex].getLetters().size(); i++) {
            players[activePlayerIndex].addLetter(pool.popLetter());
        }
    else
        cout << "You can't take more tiles from pool, because it is empty" << endl;

    players[activePlayerIndex].increaseScore(board.getNumberOfLatestCoveredWords());
}

vector<Tile> Game::getAvailableTilesForUser() {
    vector<Tile> result;

    for (auto &tile : board.getAvailableLetters()) {
        for (auto &letter : players[activePlayerIndex].getLetters())
            if (tile.letter == letter)
                result.push_back(tile);
    }

    return result;
}

Tile Game::getTile() {
    string input;
    bool inputIsValid = true;
    Tile tile(' ');
    int x, y;

    do {
        if (!inputIsValid)
            cout << "You entered invalid coordinates. Try again." << endl;
        cout << "Your tile: ";
        getline(cin, input);

        if (input.size() != 2 || (int) input[0] < 65 || (int) input[0] > 64 + board.getDimensionX() ||
            (int) input[1] < 97 || (int) input[1] > 96 + board.getDimensionY()) {
            inputIsValid = false;
            continue;
        }
        inputIsValid = true;
        x = (int) input[0] - 65;
        y = (int) input[1] - 97;
        tile = Tile(board.getTile(x, y), x, y);
    } while (!inputIsValid);

    return tile;
}

void Game::changeLetters(int tilesToCover) {
    string input;
    char letter;

    printDefaultInformation();
    cout << "You can't cover " << tilesToCover << " tiles. Change tiles." << endl;

    do {
        cout << "Enter letter that you want to change: ";
        getline(cin, input);

        if (input.size() == 1) {
            auto it = find(players[activePlayerIndex].getLetters().begin(),
                           players[activePlayerIndex].getLetters().end(), input[0]);
            if (it == players[activePlayerIndex].getLetters().end()) {
                cout << "You have to enter one of yours letter" << endl;
                players[activePlayerIndex].printLetters();
            } else {
                letter = players[activePlayerIndex].getLetters()[distance(
                        players[activePlayerIndex].getLetters().begin(), it)];
                players[activePlayerIndex].removeLetter(letter);
                players[activePlayerIndex].addLetter(pool.popLetter());
                pool.addLetter(letter);
                tilesToCover--;
            }
        } else {
            cout << "Input invalid. Just SINGLE letter" << endl;
        }
    } while (tilesToCover > 0);
}

// Clean console according to code published in moodle
void Game::clean() {
    COORD upperLeftCorner = {0, 0};
    DWORD charsWritten;
    DWORD conSize;
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    GetConsoleScreenBufferInfo(hCon, &csbi);
    conSize = csbi.dwSize.X * csbi.dwSize.Y;

    FillConsoleOutputCharacter(hCon, TEXT(' '), conSize, upperLeftCorner, &charsWritten);
    GetConsoleScreenBufferInfo(hCon, &csbi);
    FillConsoleOutputAttribute(hCon, csbi.wAttributes, conSize, upperLeftCorner, &charsWritten);

    SetConsoleCursorPosition(hCon, upperLeftCorner);
}

void Game::printDefaultInformation() {
    string score = "Score: ";
    for(auto &player : players)
        score += player.getName() + " = " + to_string(player.getScore()) + "  ";
    clean();
    cout << players[activePlayerIndex].getName() << "'s turn. " << score << endl << endl;
    board.print();
    players[activePlayerIndex].printLetters();
}

void Game::announceWinner() {
    board.print();
    auto player = max_element(players.begin(), players.end(),
                              [](const Player &a, const Player &b) { return a.getScore() < b.getScore(); });
    cout << endl << "Winner is player: " << player->getName() << endl << endl;
    system("pause >nul | set /p = Press any key to exit...");
}