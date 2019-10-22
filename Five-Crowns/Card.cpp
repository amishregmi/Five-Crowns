#include "Card.h"


/* *********************************************************************
Function Name: Card
Purpose: Default constructor of card class.
Parameters:
	face, the string face value passed by value.
	suit, the string suit value passed by value.
Assistance Received: none
********************************************************************* */

Card::Card(string face, string suit) {
	this->face = face;
	this->suit = suit;
}

/* *********************************************************************
Function Name: getFace
Purpose: To get the face of the current card
Return Value: The face of the current card as a string
Assistance Received: none
********************************************************************* */

const string Card::getFace() {
	return face;
}

/* *********************************************************************
Function Name: getSuit
Purpose: To get the suit of the current card
Return Value: The suit of the current card as a string
Assistance Received: none
********************************************************************* */

const string Card::getSuit() {
	return suit;
}

/* *********************************************************************
Function Name: setFace
Purpose: To set the face of the current card
Parameters:
	face, the string of the face to set for the current card
Assistance Received: none
********************************************************************* */

void Card::setFace(string face) {
	face = face;
}

/* *********************************************************************
Function Name: setSuit
Purpose: To set the suit of the current card
Parameters:
	suit, the string of the suit to set for the current card
Assistance Received: none
********************************************************************* */

void Card::setSuit(string suit) {
	suit = suit;
}

/* *********************************************************************
Function Name: printCard
Purpose: Prints the current card to the console
Assistance Received: none
********************************************************************* */

void Card::printCard() {
	cout <<  this->face <<  this->suit << "  ";
}

/* *********************************************************************
Function Name: cardToString
Purpose: Returns a string concatenation of the face and suit
Return Value: String containing two characters, where the first character is face and second is suit
Assistance Received: none
********************************************************************* */

string Card::cardToString() {
	return face + suit;
}

//Default Destructor

Card::~Card()
{
}
