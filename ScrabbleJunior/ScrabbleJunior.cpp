#include "ScrabbleJunior.h"

using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

void Game::startGame() {
	
// get # of players, get names and print them
	//getPlayers();
	getNumberOfPlayers();
	for (int i = 0; i < numberOfPlayers; i++) {
		Player newPlayer= Player();
		newPlayer.getName();
		players.push_back(newPlayer);
	}
	cout << "Our players are: ";
	for (int j = 0; j < players.size(); j++) {
		cout << players[j].name<<" ";
	}

// set pool and print it
	cout << "\n POOL BEFORE DRAW: \n";
	cout <<"\n" <<board.pool.size()<<"\n";
	for (int k = 0; k < board.pool.size(); k++)
		cout << board.pool[k] << " ";

// draw tiles and print
	cout << "\n PLAYER'S TILES: \n";
	drawTiles();
	for(int temp=0;temp<players.size();temp++)
		for (int l = 0; l < players[temp].letters.size(); l++) {
			cout << players[temp].letters[l] << " ";
		}

// print pool after draw
	cout <<"\n"<< board.pool.size()<<endl;
	cout << "\n POOL AFTER DRAW: \n";
	for(int t=0;t<board.pool.size();t++)
		cout << board.pool[t] << " ";
}


int Game::getNumberOfPlayers() {
	int input;
	bool keepGoing=true;
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

Player::Player() {
	name = "";
	score = 0;
}
void Player::getName() {
	cout << "Your name: " << endl;
	cin >> name;
}

// Initialization of random letters in the pool
Board::Board() {
	scoringChips = 44;
	int numOfTiles = 15;
	char letter;

	srand(time(NULL));							// to make initialization random using time seed
	for (int i = 0; i < numOfTiles; i++)
	{
		letter = 'a' + rand() % 26;            // Convert to a character from a-z
		pool.push_back(letter);
	}
}

void  Game::drawTiles(){
	int r, numOfPlayersTile = 7;

	srand(time(NULL));
	for(int i=0;i<players.size();i++){
		for (int j= 0; j < numOfPlayersTile; j++) {
			r = rand() % board.pool.size();
			players[i].letters.push_back(board.popLetter(r));
		}
	}

}

char Board::popLetter(int index) {
	char result;
	result = pool[index];
	pool.erase(pool.begin() + index);
	return result;
}