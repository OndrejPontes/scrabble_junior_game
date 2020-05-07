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

	board.setPool(board.pool);
	cout <<"\n" <<board.pool.size()<<"\n";
	for (int k = 0; k < board.pool.size(); k++)
		cout << board.pool[k] << " ";

// draw tiles and print
	cout << "\n PLAYER'S TILES: \n";
	vector<int> toRemove= players[0].drawTiles(board.pool);
	for(int temp=0;temp<players[0].playersPool.size();temp++)
		cout << players[0].playersPool[temp] << " ";

// remove tiles, which were draw from pool
	board.removeTilesFromPool(toRemove);

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

Board::Board() {
	scoringChips = 44;
}

void Board::setPool(vector<char> &pool) {
    int numOfTiles = 101;
	char letter;

	srand(time(NULL));
	for (int i = 0; i < numOfTiles; i++)
	{
		letter = 'a' + rand() % 26;            // Convert to a character from a-z
		pool.push_back(letter);
	}

}

vector<int> Player::drawTiles(std::vector<char> pool){
	int r, numOfPlayersTile = 7;
	vector<int> toRemove;
	srand(time(NULL));
	for (int i = 0; i < numOfPlayersTile; i++) {
		r = rand() % pool.size();
		playersPool.push_back(pool[r]);
		toRemove.push_back(r);
		cout << r << " ";
	}

	return toRemove;
}

void Board::removeTilesFromPool(vector<int> toRemove) {
	for(int i=0;i<toRemove.size();i++){
		pool.erase(pool.begin() + toRemove[i]);
	}

}