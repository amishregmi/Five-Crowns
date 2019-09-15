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

void Card::setFace(string face) {
	face = face;
}

void Card::setSuit(string suit) {
	suit = suit;
}

string Card::cardToString() {
	return face + suit;
}

Card::~Card()
{
}
