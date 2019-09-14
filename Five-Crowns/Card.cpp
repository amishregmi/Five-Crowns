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
	cout <<  this->face <<  this->suit << "  ";
}

Card::~Card()
{
}
