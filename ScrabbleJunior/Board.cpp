#include "Board.h"
#include "../Board.h"


using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>


void Board::showPool() {
	cout << "\n OUR POOL IS: \n";
	cout << "\nNumber of letters in pool: " << pool.size() << "\n";
	for (int k = 0; k < pool.size(); k++)
		cout << pool[k] << " ";

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

char Board::popLetter(int index) {
	char result;
	result = pool[index];
	pool.erase(pool.begin() + index);
	return result;
}


std::string Word::toString() {
    return std::string();
}
