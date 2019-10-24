#include "Human.h"

//Default constructor

Human::Human()
{
}

/* *********************************************************************
Function Name: pickCardHelp
Purpose: To print to console the recommendation on whether to pick card from draw or discard pile
Parameters:
	None
Return Value: None
Local Variables:
	topDiscardCard, card at the top of Discard pile
	topDrawCard, card at the top of the draw pile
	reason, string containing the reason for the recommendation
	points_before_adding_discard_card, an integer containing the sum of cards remaining after best book/run combination before picking discard
	points_before_adding_discard_card, an integer containing the sum of cards remaining after best book/run combination after picking discard card
	check_if_goout, a boolean to check if human can go out
Algorithm:
	1) Check if the top discard card is joker or wildcard. If so, set the reason as such.
	2) Calculate points of cards remaining after forming best bookrun combination before and after adding top discard card to hand. If the points after adding the card is less than 
	points before adding the card, set reason to recommend picking card from top of discard pile, else from top of draw pile
Assistance Received: none
********************************************************************* */

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
		int points_before_adding_discard_card = getHandScore();
		addCardToHand(topDiscardCard);
		bool check_if_goout = goOut();

		if (check_if_goout) {
			reason = "I recommend picking card from top of discard pile since it helps you assemble cards to goOut";
		}
		else {
			int points_after_adding_discard_card = getHandScore();
			if (points_after_adding_discard_card <= points_before_adding_discard_card) {
				reason = "I recommend picking card from top of discard pile since it helps form a better book/run combination and get a hand where sum of remaining cards is lower or equal";
			}

			else {
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

/* *********************************************************************
Function Name: pickCard
Purpose: To add a card to the user's hand based on user's choice to pick from either top of discard or draw pile.
Parameters: 
	None
Return Value: None
Local Variables:
	draw_or_discard, a character containing user's choice for what card to pick
	drop_help, a character to see if the user wants help with which card to drop
Assistance Received: none
********************************************************************* */

void Human::pickCard() {
	checkWildcards();
	checkJokercards();
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

/* *********************************************************************
Function Name: dropCardHelp
Purpose: To print to console the recommendation on the index of the card to drop
Parameters:
	None
Return Value: None
Local Variables:
	reason, string containing the reason for the recommendation
	points_after_drop, an integer of vector containing the sum of remaining cards after forming best book/run combination after dropping cards at every index.
	current_index, an integer containing the current index
	temp, a temporary vector of cards to save the current player's hand
	temp_str, a temporary vector of strings save the current player's hand representation in string
	min, an integer containing the minimum value in the vector of integers points_after_drop
	required_index, the index corresponding to the card to drop
Algorithm:
	1) Remove card at each index, computer the sum of points of cards remaining after forming best book/run combination of remaining cards and push that to a vector of integers
	2) For the indexes that don't correspond to a wildcard or a joker, find the minimum value in the vector of integers and recommend for that card to be dropped.
Assistance Received: none
********************************************************************* */

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
		points_after_drop.push_back(getHandScore());

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

/* *********************************************************************
Function Name: dropCard
Purpose: To drop a card in the index specified by the user.
Parameters:
	None
Return Value: None
Local Variables:
	del_indexx, a string containing the user input for the card they want to drop
	del_index, an integer containing the user input for the card they want to drop
	notalldigits, a boolean to check if all the numbers in the input are digits
	numbernotinrange, a boolean to check if the integer entered by the user is within the range of 0 to total number of cards in hand - 1
Assistance Received: none
********************************************************************* */

void Human::dropCard() {
	string del_indexx;
	cout << "Enter the index of the card you want to delete: ";
	cin >> del_indexx;
	int del_index;
	bool notalldigits = true;
	bool numbernotinrange = false;

	do {
		if (numbernotinrange) {
			cout << "The number is not in range. Please enter valid index: ";
			cin >> del_indexx;
		}

		if (!(any_of(del_indexx.begin(), del_indexx.end(), isdigit)) ) {

			cout << "Invalid input. Please enter index of card you want to delete: ";
			cin >> del_indexx;
		}
		else {
			del_index = stoi(del_indexx);
			
			if (del_index > (total_cards_in_hand - 1) || del_index < 0) {
				numbernotinrange = true;
			}
			else {
				numbernotinrange = false;
			}
			notalldigits = false;
		}
	} while (notalldigits || numbernotinrange);

	
	Card card_dropped = current_player_hand.at(del_index);
	current_player_hand.erase(current_player_hand.begin() + del_index);
	total_cards_in_hand--;
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

/* *********************************************************************
Function Name: booksAndRunsAndGoOut
Purpose: Function to get help on assembling books and runs and check if the user can go out
Parameters:
	None
Return Value: None
Assistance Received: none
********************************************************************* */

void Human::booksRunsAndGoOut() {
	goOut();
	
	if (getHandScore() == 0) {
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

//Default Constructor

Human::~Human()
{
}
