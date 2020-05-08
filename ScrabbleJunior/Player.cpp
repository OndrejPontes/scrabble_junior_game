#include "Player.h"
using namespace std;
#include <iostream>

Player::Player() {
	name = "";
	score = 0;
}
void Player::getName() {
	cout << "Your name: " << endl;
	cin >> name;
}


