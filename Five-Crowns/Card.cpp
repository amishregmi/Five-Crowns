#include "Card.h"


Card::Card(string face, string suit) {
	this->face = face;
	this->suit = suit;
}

string Card::getFace() {
	return face;
}

string Card::getSuit() {
	return suit;
}


void Card::printCard() {
	cout << "Face: " << this->face << " " << "Suit: " << this->suit << endl;
}

Card::~Card()
{
}
