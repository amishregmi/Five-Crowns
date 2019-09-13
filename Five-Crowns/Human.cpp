#include "Human.h"



Human::Human()
{
}

void Human::addCardToHand(Card card) {
	human_hand.push_back(card);
}

void Human::printCurrentHard() {
	cout << "Printing human hand" << endl;
	vector<Card> ::iterator it;
	for (it = human_hand.begin(); it != human_hand.end(); ++it) {
		it->printCard();
	}
	cout << endl;
}

Human::~Human()
{
}
