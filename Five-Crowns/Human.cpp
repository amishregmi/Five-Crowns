#include "Human.h"

Human::Human()
{
}


void Human::pickCard() {
	//menuOptions();
	checkWildcards();
	checkJokercards();
	//cout << "Inside human pickCard() " << total_cards_in_hand << endl;
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
		Card topDrawCard = Deck::takeTopDrawCard();
		addCardToHand(topDrawCard);
	}

	else {
		Card topDiscardPile = Deck::takeTopDiscardCard();
		addCardToHand(topDiscardPile);
	}

	dropCard();
	
}



void Human::dropCard() {
	cout << "Before dropping card, ";
	printCurrentHand();
	int del_index;
	cout << "Enter the index of the card you want to delete: ";
	cin >> del_index;

	if (del_index > (total_cards_in_hand - 1)) {
		do {
			cout << "Invalid input. Please enter index within range: ";
			cin >> del_index;
		} while (del_index > (total_cards_in_hand - 1));
	}

	Card card_dropped = current_player_hand.at(del_index);
	current_player_hand.erase(current_player_hand.begin() + del_index);
	total_cards_in_hand--;
	Deck::discardPile.push_back(card_dropped);
	current_player_hand_str.erase(current_player_hand_str.begin() + del_index);
	checkWildcards();
	checkJokercards();

	
}


Human::~Human()
{
}
