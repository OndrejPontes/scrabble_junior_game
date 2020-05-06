#include "ScrabbleJunior.h"

using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void Game::startGame() {
	getNumberOfPlayers();
	for (int i = 1; i <= numberOfPlayers; i++) {
		Player player= Player();
		player.getName();
		players.push_back(player);
	}


}


int Game::getNumberOfPlayers() {
	cout << "Enter number of players: "<<endl;
	cin >> numberOfPlayers;
	system("CLS");
	return numberOfPlayers;
}