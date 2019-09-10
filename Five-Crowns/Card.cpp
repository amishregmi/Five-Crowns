#include "Card.h"



Card::Card()
{
}

string Card::getFace() {
	return face;
}

string Card::getSuit() {
	return suit;
}

void Card::setFace(string face) {
	this->face = face;
}

void Card::setSuit(string suit) {
	this->suit = suit;
}

void Card::printCard() {
	cout << "Face: " << this->face << " " << "Suit: " << this->suit << endl;
}

Card::~Card()
{
}
