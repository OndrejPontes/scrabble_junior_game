#include "Game.h"

using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

void Game::startGame() {

	// get # of players, get names and print them
	getPlayers();
	showPool();		// show pool before draw
	drawTiles();
	showPool();		// show pool after draw
	board.print();
}


int Game::getNumberOfPlayers() {
	int input;
	bool keepGoing = true;
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
	// print player's tiles
	cout << "\n PLAYER'S TILES: \n";
	for (int temp = 0; temp < players.size(); temp++)
		for (int l = 0; l < players[temp].letters.size(); l++) {
			cout << players[temp].letters[l] << " ";
		}

}

char Game::popLetter(int index) {
	char result;
	result = pool[index];
	pool.erase(pool.begin() + index);
	return result;
}

// Initialization of random letters in the pool
Game::Game() {
	int scoringChips = 44;
	int numOfTiles = 15;
	char letter;

	srand(time(NULL));							// to make initialization random using time seed
	for (int i = 0; i < numOfTiles; i++)
	{
		letter = 'a' + rand() % 26;            // Convert to a character from a-z
		pool.push_back(letter);
	}
}

void Game::showPool() {
	cout << "\n OUR POOL IS: \n";
	cout << "\nNumber of letters in pool: " << pool.size() << "\n";
	for (int k = 0; k < pool.size(); k++)
		cout << pool[k] << " ";

}