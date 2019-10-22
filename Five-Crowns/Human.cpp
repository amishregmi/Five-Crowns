#include "Human.h"

Human::Human()
{
}

void Human::pickCardHelp() {
	Card topDiscardCard = Deck::accessTopDiscardPileCard();
	Card topDrawCard = Deck::accessTopDrawPileCard();

	string reason;

	if (checkIfJoker(topDiscardCard.cardToString())) {
		reason = "I recommend picking card from top discard pile since it's a joker";
	}

	else if (checkIfWildcard(topDiscardCard.cardToString())) {
		reason = "I recommend picking card from top discard pile since it's a wildcard";
	}

	else {
		//Not wildcard or joker
		goOut();
		int points_before_adding_discard_card = hand_score;
		addCardToHand(topDiscardCard);
		bool check_if_goout = goOut();

		if (check_if_goout) {
			reason = "I recommend picking card from top of discard pile since it helps you assemble cards to goOut";
		}
		else {
			int points_after_adding_discard_card = hand_score;
			if (points_after_adding_discard_card <= points_before_adding_discard_card) {
				reason = "I recommend picking card from top of discard pile since it helps form a better book/run combination and get a hand where sum of remaining cards is lower or equal";
			}

			else {
				//int drop_index = total_cards_in_hand - 1;
				//current_player_hand.erase(current_player_hand.begin() + drop_index);
				//total_cards_in_hand--;
				//current_player_hand_str.erase(current_player_hand_str.begin() + drop_index);

				reason = "I recommend picking card from top of Draw pile because top of discard pile is neither a wildcard, nor a joker, and does not help form a better book/run combination or help you goout";
			}
		}

		current_player_hand.erase(current_player_hand.begin() + total_cards_in_hand - 1);
		current_player_hand_str.erase(current_player_hand_str.begin() + total_cards_in_hand - 1);
		total_cards_in_hand--;

	}

	

	cout << "Recommendation: ";
	cout << reason << endl;

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

	
	//cout << "ABOUT to add card to hand " << endl;

	if (tolower(draw_or_discard) == 'a') {
		Card topDrawCard = Deck::takeTopDrawCard();
		//cout << "About to add the card " << endl;
		//topDrawCard.printCard();
		addCardToHand(topDrawCard);
		//cout << "Printing inside if";
		//printCurrentHand();
	}

	else {
		Card topDiscardPile = Deck::takeTopDiscardCard();
		//cout << "About to add the card " << endl;
		//topDiscardPile.printCard();
		addCardToHand(topDiscardPile);
		//cout << "Printing inside else";
		//printCurrentHand();
	}

	char drop_help;


	cout << "Before dropping card, ";
	printCurrentHand();
	
	cout << "Press y to get help for which card to drop. Press any other key otherwise: ";
	cin >> drop_help;



	if (drop_help == 'y' || drop_help == 'Y') {
		dropCardHelp();
	}
	
	dropCard();
	
}

void Human::dropCardHelp() {
	string reason;
	vector<int> points_after_drop;
	int current_index = 0;
	vector<Card> temp = current_player_hand;
	vector<string> temp_str = current_player_hand_str;

	while (current_index < total_cards_in_hand) {
		current_player_hand.erase(current_player_hand.begin() + current_index);
		total_cards_in_hand--;
		current_player_hand_str.erase(current_player_hand_str.begin() + current_index);
		goOut();
		points_after_drop.push_back(hand_score);

		//RESET VALUES
		current_player_hand = temp;
		total_cards_in_hand++;
		current_player_hand_str = temp_str;
		current_index++;
	}

	int min = INT_MAX;
	int required_index;

	for (int i = 0; i < points_after_drop.size(); i++) {
		if (!(checkIfJoker(current_player_hand_str[i]) || checkIfWildcard(current_player_hand_str[i]))) {
			if (points_after_drop[i] < min) {
				reason = "I recommend you drop card at index " + to_string(i) + " because it's not a wildcard or joker and helps decrease the sum of cards that remain after the best book/run combination in hand";
				if (points_after_drop[i] == 0) {
					reason = "I recommend you drop card at index: " + to_string(i) + " because you can go out with remaining cards";
				}
				min = points_after_drop[i];
				required_index = i;
			}
		}
	}

	cout << "Recommendation: ";
	cout << reason << endl;

}



void Human::dropCard() {

	string del_indexx;
	cout << "Enter the index of the card you want to delete: ";
	cin >> del_indexx;
	int del_index;
	bool notalldigits = true;

	do {

		if (!(any_of(del_indexx.begin(), del_indexx.end(), isdigit))) {

			cout << "Number not entered. Please enter index of card you want to delete: ";
			cin >> del_indexx;
		}
		else {
			del_index = stoi(del_indexx);
			notalldigits = false;
		}
	} while (notalldigits);

	//cout << endl;
	/* TODO -> THIS IS WORKING CODE
	if ( !( del_index >=0 && del_index < total_cards_in_hand )) {
		do {
			cout << "Invalid input. Please enter index within range: ";
			cin >> del_indexx;
			del_index = stoi(del_indexx);
		} while ((del_index > (total_cards_in_hand - 1)) || del_index < 0);
	} */

	Card card_dropped = current_player_hand.at(del_index);
	current_player_hand.erase(current_player_hand.begin() + del_index);
	total_cards_in_hand--;
	//TODO changed below from working version
	//Deck::discardPile.push_back(card_dropped);
	Deck::pushToDiscardPile(card_dropped);
	current_player_hand_str.erase(current_player_hand_str.begin() + del_index);
	checkWildcards();
	checkJokercards();

	char after_drop_help;
	cout << "Press y to get help for books and runs and see if you can go out: ";
	cin >> after_drop_help;

	if (after_drop_help == 'y' || after_drop_help == 'Y') {
		booksRunsAndGoOut();
	}
	
	
}

void Human::booksRunsAndGoOut() {
	goOut();
	
	if (hand_score == 0) {
		cout << "You will be able to go out now" << endl;
	}
	else {
		cout << "You cannot go out because cards remain in your hand not a part of book or run " << endl;
	}

	if (child_returning_smallest_sum.size() == 0) {
		cout << "Couldn't find any combination of books and runs in the current hand: " << endl;
	}
	else {
		cout << " I recommend the following combination for books and runs: " << endl;
		for (auto i = child_returning_smallest_sum.begin(); i < child_returning_smallest_sum.end(); i++) {
			cout << *i << "   ";
		}
		cout << endl;

	}
}

Human::~Human()
{
}
