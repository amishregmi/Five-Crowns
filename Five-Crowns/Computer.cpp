#include "Computer.h"



Computer::Computer()
{
}



void Computer::pickCard() {
	//cout << "Computer at start of pickCard total cards" << total_cards_in_hand << endl;
	Card topDiscardCard = Deck::accessTopDiscardPileCard();
	
	Card topDrawCard = Deck::accessTopDrawPileCard();
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
		int points_before_adding_discard_card = hand_score;
		addCardToHand(topDiscardCard);
		bool check_if_goout = goOut();
		if (check_if_goout) {
			reason = "Computer picked from top of Discard pile because it helps to goOut ";
			Deck::takeTopDiscardCard();
		}
		else {
			int points_after_adding_discard_card = hand_score;

			if (points_after_adding_discard_card < points_before_adding_discard_card) {
				reason = "Computer picked from top of Discard pile because it helps in a better book/run combination in hand ";
				Deck::takeTopDiscardCard();
			}

			else {
				//No use of top Discard Card;
				int drop_index = total_cards_in_hand - 1;
				//Card drop_topdiscardcard_fromhand = current_player_hand.at(drop_index);
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

void Computer::dropCard() {
	
	string reason; 
	cout << "Before dropping card, ";
	printCurrentHand();
	
	//Remove card at every index and calculate score and push scores in vector
	//index of vector element corresponding to lowest sum is the card you want to drop.
	vector<int> points_after_drop;
	int current_index = 0;

	vector<Card> temp = current_player_hand;
	vector<string> temp_str = current_player_hand_str;

	//cout << "Total cards in hand is: " << total_cards_in_hand << endl;
	
	while (current_index < total_cards_in_hand) {

		//cout << "current_index is: " << current_index << endl;
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
		//cout << "Before while again " << endl;
	}

	//cout << "Printing points after dropping card at every index " << endl;

	//int i = 0;
	int min = INT_MAX;
	int required_index;

	for (int i = 0; i < points_after_drop.size(); i++) {
		if (!( checkIfJoker(current_player_hand_str[i]) || checkIfWildcard(current_player_hand_str[i] ))) {
			if (points_after_drop[i] < min) {
				if (points_after_drop[i] == 0) {
					reason = "Dropping card at index " + to_string(i) + "because the player can go out ";
				}
				reason = "Dropping card at index " + to_string(i) + "because it's not a wildcard/joker and helps decrease sum of cards remaining after book/run combination";
				min = points_after_drop[i];
				required_index = i;
			}
		}
	}

	cout << reason << endl;

	//cout << endl;
	
	int randNum = required_index;
	//cout << "Computer is dropping card at index: " << randNum << endl;
	//cout << "The current computer hand is: ";
	
	Card card_dropped = current_player_hand.at(randNum);
	current_player_hand.erase(current_player_hand.begin() + randNum);
	total_cards_in_hand--;
	Deck::discardPile.push_back(card_dropped);
	current_player_hand_str.erase(current_player_hand_str.begin() + randNum);

	printCurrentHand();

	//cout << endl;
}

Computer::~Computer()
{
}
