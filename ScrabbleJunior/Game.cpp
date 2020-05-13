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

void Game::startGame() {


	getPlayers();
	showPool();		
	drawTiles();
	showPool();		// show pool after draw
	Board::loadFromFile("test").print();
	coverTiles();

}

int Game::getNumberOfPlayers() {
	int input;
	bool keepGoing = true;
	system("CLS");
	while (keepGoing) {
		cout << "Enter number of players(2-4): ";
		cin >> input;
		// if user enter character instead of number
		if (cin.fail()) {
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Please enter a valid value!\n";
		}
		else if ((input >= 2 && input <= 4)) {
			numberOfPlayers = input;
			keepGoing = false;
		}
	}
	system("CLS");
	return numberOfPlayers;
}

void Game::coverTiles()
{
	int posX, posY;
	vector<string> parsed;
	string line;
	bool keepGoing=true;
	cout << "Enter tile that you want to cover in format  'Ak T'. The first pair represents the coordinates where you want to place the tile."
		"Second parameter is your tile."<<endl;
	cin.ignore();
	// while user's input is not correct, user must enter tile again
	while (keepGoing) {
		cout << "\nYour tile: ";
		
		getline(cin, line);
		istringstream iss(line);
		parsed = {
				istream_iterator<string>(iss), {}
		};
		posX = (int)parsed[0][0] - 64;
		posY = (int)parsed[0][1] - 96;
		if ((parsed.size() == 2) && (parsed[0].size() == 2) && (posX >= 1) && (posX <= board.getDimensionX()) && (posY >= 1) && (posY <= board.getDimensionY())) {

			if (parsed[1][0] != board.getTile((int)parsed[0][0], (int)parsed[0][1]) && find(players[0].letters.begin(), players[0].letters.end(), parsed[1][0])
				== players[0].letters.end()) {
				cout << "You can't cover this tile!";
			}
			else {
				board.takeTile((int)parsed[0][0], (int)parsed[0][1]);
				keepGoing = false;
			}
		}
		else {
			cout << " Enter excatly 2 parameters and check if parameters  do not exceeds dimensions of board! ";
		}

	}
} 

void Game::getPlayers() {
	getNumberOfPlayers();
	for (int i = 0; i < numberOfPlayers; i++) {
		Player newPlayer = Player();
		newPlayer.getName();
		players.push_back(newPlayer);
	}
	cout << "Our players are: ";
	for (int j = 0; j < players.size(); j++) {
		cout << players[j].name << " ";
	}
	system("CLS");
}

void  Game::drawTiles() {
	int r, numOfPlayersTile = 7;

	srand(time(NULL));
	for (int i = 0; i < players.size(); i++) {
		for (int j = 0; j < numOfPlayersTile; j++) {
			r = rand() % pool.size();
			players[i].letters.push_back(popLetter(r));
		}
	}
	showPlayersTiles();

	
}

char Game::popLetter(int index) {
	char result;
	result = pool[index];
	pool.erase(pool.begin() + index);
	return result;
}

// Initialization of random letters in the pool
Game::Game() {
	getSettings();
	char letter;
	srand(time(NULL));							// to make initialization random using time seed
	for (int i = 0; i < numOfTiles; i++)
	{
		letter = 'a' + rand() % 26;            // Convert to a character from a-z
		pool.push_back(letter);
	}
}

void Game::getSettings()
{// initialization parameters of game
	int input;
	bool keepGoing =true;
	cout << "\t\tWELCOME TO SCRABBLE GAME !\nFirst of all, let's go through the game settings.\n\n";
	while (keepGoing) {
		cout << "How many tiles do you want to play with(Minimum value for two players is 14): ";
		cin >> input;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Enter valid value!\n";
		}
		else if(input >= 14){
			keepGoing = false;
			numOfTiles = input;
		}
	}

}

void Game::showPool() {
	string input;
	// with 101 letters in pool, it might be unclear in terminal
	cout << "\nIf you want to see pool, press 'y': ";
	cin >> input;
	if (input == "y") {
		cout << "OUR POOL IS: \n";
		for (int k = 0; k < pool.size(); k++)
			cout << pool[k] << " ";
		cout << "\nNumber of letters in pool: " << pool.size() << "\n";
		
	}

}

void Game::showPlayersTiles()
{
	cout << endl << " PLAYER'S TILES: " << endl;
		for (int temp = 0; temp < players.size(); temp++) {
			cout << "Player " << temp << ".: ";
			for (int l = 0; l < players[temp].letters.size(); l++) {
				cout << players[temp].letters[l] << " ";

			}
			cout << endl;
		}
}

