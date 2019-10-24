#include "Computer.h"

//Default constructor for Computer class

Computer::Computer()
{
}

/* *********************************************************************
Function Name: pickCard
Purpose: To decide whether the computer is going to pickCard from the top of discard pile
or draw pile and the add the card picked to the hand, and print reason to the console.
Local Variables:
	reason, a string used store the reason why the computer decided to pick from a certain pile
	points_before_adding_discard_card, an integer that computes the sum of all cards in the current hand that are not part of the best book/run combination
	points_after_adding_discard_card, an integer that computers sum of all cards in the current hand after adding a particular card that are not part of the best book/run combination
Algorithm:
	1) Access the top card from discard pile and check if it's a wildcard or a joker. If so, add the card to hand
	2) If not wildcard or joker, computer the best book/run combination of cards in the current hand and computer sum of remaining cards.
	3) Add the top discard card and computer best book/run combination again to calculate sum of remaining cards. 
	4) If the sum of remaining cards after adding top discard card is less than or equal to the sum of cards before picking a card, pick
	card from top of discard pile. Else, pick card from draw pile.
Assistance Received: none
********************************************************************* */

void Computer::pickCard() {
	Card topDiscardCard = Deck::accessTopDiscardPileCard();
	Card topDrawCard = Deck::accessTopDrawPileCard();
	//string to hold the reason for picking up a particular card
	string reason; 

	//If topDiscardCard is wildcard or joker, add the card to hand.
	if (checkIfJoker(topDiscardCard.cardToString())) {
		reason = "Computer picked from top of Discard pile because the card is a joker";
		addCardToHand(topDiscardCard);
	}

	else if (checkIfWildcard(topDiscardCard.cardToString())) {
		reason = "Computer picked from top of Discard pile because the card is a wildcard ";
		addCardToHand(topDiscardCard);
	}

	else {
		//Try adding card to hand and check if computer can go out.
		goOut();
		//store the calculated sum of cards not part of the best combination of books and runs in current hand
		int points_before_adding_discard_card = getHandScore();
		addCardToHand(topDiscardCard);
		//boolean to check if the computer can go out
		bool check_if_goout = goOut();
		if (check_if_goout) {
			reason = "Computer picked from top of Discard pile because it helps to goOut ";
			Deck::takeTopDiscardCard();
		}
		else {
			//stores the calculated sum of cards not part of the best combination of books and runs in current hand after adding top discard card to hand.
			int points_after_adding_discard_card = getHandScore();

			if (points_after_adding_discard_card <= points_before_adding_discard_card) {
				reason = "Computer picked from top of Discard pile because it helps in a better book/run combination in hand ";
				Deck::takeTopDiscardCard();
			}

			else {
				//Stores index corresponding to the top discard card picked
				int drop_index = total_cards_in_hand - 1;
				current_player_hand.erase(current_player_hand.begin() + drop_index);
				total_cards_in_hand--;
				current_player_hand_str.erase(current_player_hand_str.begin() + drop_index);
				reason = "Computer picked from top of Draw Pile because discard pile didn't have wildcard or joker and didn't help assemble a better book/run combination ";
				addCardToHand(Deck::takeTopDrawCard());
			}
		}
	}

	cout << reason << endl;
	dropCard();

}

/* *********************************************************************
Function Name: dropCard()
Purpose: To drop a card from the current hand.
Local Variables:
	reason, a string used store the reason why the computer decided to drop a certain card from the hand.
	points_after_drop, a vector of integers that stores the sum of cards not part of book or run after removing each card from the current hand and calculating sum of remaining cards after forming the best book/run combination.
	temp, a vector of cards used to hold the current player hand to restore the original values after manipulation
	temp_str, a vector of string containing the current player hand in string representation
	current_index, an integer that holds the current index position of the card that is being dropped
	min, an integer that is used to find the minimum value of the points_after_drop vector of integers.
	required_index, an integer that stores the index position in points_after_drop of card that is to be dropped.
	points_before_adding_discard_card, an integer that computes the sum of all cards in the current hand that are not part of the best book/run combination
	points_after_adding_discard_card, an integer that computers sum of all cards in the current hand after adding a particular card that are not part of the best book/run combination
Algorithm:
	1) Remove each card from the hand, computer the sum of cards not part of the best book and runs combination available. Push that sum to a vector of integers.
	2) For each element in the points_after_drop, calculate each corresponding element to the current hand. If it's not a wildcard or a joker, check if it's the minimum element in the vector.
	3) Remove the card corresponding to the lowest integer and print information on the card dropped to the console.
Assistance Received: none
********************************************************************* */

void Computer::dropCard() {
	//string to hold reason for dropping a particular card
	string reason; 
	cout << "Before dropping card, ";
	printCurrentHand();
	//vector of integers to store the sum of remaining cards not part of best combination containing books and runs after dropping a card 
	vector<int> points_after_drop;
	//holds the index of the current card to drop
	int current_index = 0;
	//holds the vector of card of current hand to reset values after deleting a card
	vector<Card> temp = current_player_hand;
	//holds the vector of string representation of card of current hand to reset values after deleting a card string
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

	//minimum number used to compute the minimum value in the vector
	int min = INT_MAX;
	//holds the index of the card to drop
	int required_index;

	for (int i = 0; i < points_after_drop.size(); i++) {
		if (!( checkIfJoker(current_player_hand_str[i]) || checkIfWildcard(current_player_hand_str[i] ))) {
			if (points_after_drop[i] < min) {
				reason = "Computer is dropping card at index " + to_string(i) + " because it's not a wildcard/joker and helps decrease sum of cards remaining after book/run combination";

				if (points_after_drop[i] == 0) {
					reason = "Computer is dropping card at index " + to_string(i) + " because the player can go out with remaining cards ";
				}
				
				min = points_after_drop[i];
				required_index = i;
			}
		}
	}

	cout << reason << endl;
	
	//Drop the card
	Card card_dropped = current_player_hand.at(required_index);
	current_player_hand.erase(current_player_hand.begin() + required_index);
	total_cards_in_hand--;
	Deck::pushToDiscardPile(card_dropped);
	current_player_hand_str.erase(current_player_hand_str.begin() + required_index);
	printCurrentHand();
}

//Default destructor

Computer::~Computer()
{
}
