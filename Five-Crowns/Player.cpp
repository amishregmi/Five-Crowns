#include "Player.h"



Player::Player()
{
}


void Player::addCardToHand(Card card) {
	current_player_hand.push_back(card);
}

void Player::printCurrentHand(string next_player) {
	cout << "The current player is: " << next_player << endl;
	cout << "Printing current player hand: " << endl;
	vector<Card>::iterator it;
	for (it = current_player_hand.begin(); it != current_player_hand.end(); ++it) {
		it->printCard();
	}
	cout << endl;
}

void Player::pickCard() {
	cout << "Virtual function pickCard() in Player class " << endl;
}

void Player::dropCard() {
	cout << "Virtual function dropCard() in Player class " << endl;
}

Player::~Player()
{
}
