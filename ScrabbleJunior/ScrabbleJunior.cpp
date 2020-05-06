#include "ScrabbleJunior.h"

using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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
	cout << "Enter number of players: ";
	cin >> numberOfPlayers;
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