#include "Computer.h"



Computer::Computer()
{
}

void Computer::addCardToHand(Card card) {
	computer_hand.push_back(card);
}

void Computer::printCurrentHard() {
	cout << "Printing computer hand" << endl;
	vector<Card> ::iterator it;
	for (it = computer_hand.begin(); it != computer_hand.end(); ++it) {
		it->printCard();
	}
	cout << endl;
}


Computer::~Computer()
{
}
