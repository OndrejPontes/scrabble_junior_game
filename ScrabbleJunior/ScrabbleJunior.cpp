#include "ScrabbleJunior.h"

using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

void Game::startGame() {
	

	getNumberOfPlayers();
	for (int i = 0; i < numberOfPlayers; i++) {
		Player newPlayer= Player();
		newPlayer.getName();
		players.push_back(newPlayer);
	}
	for (int j = 0; j < players.size(); j++) {
		cout << players[j].name;
	}
	cout<<board.scoringChips;
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

Board::Board() {
	scoringChips = 44;
}