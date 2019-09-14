#include "Human.h"



Human::Human()
{
}

/*

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
*/

void Human::pickCard() {
	char draw_or_discard;
	cout << "Enter a to take the top draw card and b to take the available discard card: ";
	cin >> draw_or_discard;
	if (tolower(draw_or_discard) != 'a' && tolower(draw_or_discard) != 'b') {
		do {
			cout << "Invalid Input. Please enter a to take top draw card and b to take top discard card: ";
			cin >> draw_or_discard;
		} while (tolower(draw_or_discard) != 'a' && tolower(draw_or_discard) != 'b');
	}

	if (tolower(draw_or_discard) == 'a') {
		//Take top draw card
		cout << "Human selected card from draw pile" << endl;
		Card topDrawCard = Deck::takeTopDrawCard();
		addCardToHand(topDrawCard);
		total_cards_in_hand++;
	}
	else {
		cout << "Human selected card from discard pile " << endl;
		Card topDiscardPile = Deck::takeTopDiscardCard();
		addCardToHand(topDiscardPile);
		total_cards_in_hand++;
	}
	
	dropCard();
	
}

void Human::dropCard() {
	cout << "The current player's hand is: " << endl;
	printCurrentHand();
	
}

Human::~Human()
{
}
