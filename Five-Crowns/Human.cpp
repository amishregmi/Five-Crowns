#include "Human.h"

Human::Human()
{
}

void Human::pickCard() {
	checkWildcards();
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
		//Take top draw card
		//cout << "Human selected card from draw pile" << endl;
		Card topDrawCard = Deck::takeTopDrawCard();
		addCardToHand(topDrawCard);
	}

	else {
		//cout << "Human selected card from discard pile " << endl;
		Card topDiscardPile = Deck::takeTopDiscardCard();
		addCardToHand(topDiscardPile);
	}

	//cout << "Total number of wildcards is: " << total_wildcards_num << endl;
	//cout << "After human pickcard total cardss in hand " << total_cards_in_hand << endl;
	dropCard();
	
}



void Human::dropCard() {
	//cout << "The current player's hand is: " << endl;
	//cout << "Beginning of dropCard " << total_cards_in_hand << endl;
	cout << "Before dropping card, ";
	printCurrentHand();
	//Card(face, suit)
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
	cout << "After dropping card, ";
	printCurrentHand();
	checkWildcards();
	cout << "The total number of wildcards is: " << getWildcardsNum() << endl;
	cout << endl;
	cout << endl;
	//cout << "AFter human dropcard " << total_cards_in_hand << endl;
	
}

Human::~Human()
{
}
