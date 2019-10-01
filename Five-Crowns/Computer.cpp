#include "Computer.h"



Computer::Computer()
{
}



void Computer::pickCard() {
	//cout << "Computer at start of pickCard total cards" << total_cards_in_hand << endl;
	srand(time(NULL));
	int randNum = rand() % 2;
	//cout << "Computer's randNum is: " << randNum;
	if (randNum == 0) {
		//computer picked from draw pile
		cout << "Computer picked from draw pile: " << endl;
		Card topDrawCard = Deck::takeTopDrawCard();
		addCardToHand(topDrawCard);
	}
	else {
		//computer picked from discard pile
		cout << "Computer picked from discard pile: " << endl;
		Card topDiscardPile = Deck::takeTopDiscardCard();
		addCardToHand(topDiscardPile);
	}

	//cout << "Computer before dropCard() " << total_cards_in_hand << endl;

	dropCard();

}

void Computer::dropCard() {
	//Get random index and delete that card for now
	//cout << "Total cards in hand at start of dropCard() " << total_cards_in_hand << endl;
	cout << "Before dropping card, ";
	printCurrentHand();
	int randNum = rand() % total_cards_in_hand;
	cout << "Computer is dropping card at index: " << randNum << endl;
	//cout << "The current computer hand is: ";
	
	Card card_dropped = current_player_hand.at(randNum);
	current_player_hand.erase(current_player_hand.begin() + randNum);
	total_cards_in_hand--;
	Deck::discardPile.push_back(card_dropped);
	current_player_hand_str.erase(current_player_hand_str.begin() + randNum);

	printCurrentHand();

	//checkWildcards();
	//cout << "After dropping card, ";
	//printCurrentHand();
	checkJokercards();
	checkWildcards();
	//cout << "Total cards after dropCard " << total_cards_in_hand << endl;
	//cout << "The total number of wildcards is: " << getWildcardsNum() << endl;
	//cout << "The total number of jokers is: " << getJokersNum() << endl;
	//cout << "Checking book: ";
	//cout << checkBook() << endl;
	//cout << "Checking run: ";
	//cout << checkRun() << endl;
	//cout << endl;
	cout << endl;
}

Computer::~Computer()
{
}
