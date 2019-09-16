#include "Round.h"


Round::Round(int roundNumber = 0)
{
	this->roundNumber = roundNumber;
	//Determine next_player_index by coin toss.
	this->next_player_index = 0;
	this->playersList[0] = &human_player;
	this->playersList[1] = &computer_player;
	this->next_player = "user";
	this->total_players_num = 2;
	this->verify_go_out = false;
}

void Round::dealForRound() {
	//Distribute cards to both players based on round number, and add one card to discard pile.
	vector<Card> dealtCards = deck.dealCards(roundNumber);
	vector<Card>::iterator it = dealtCards.begin();

	if (!dealtCards.empty()) {
		for (size_t i = 0; i < (dealtCards.size() - 1); i += 2) {
			//human_player.addCardToHand(dealtCards[i]);
			//computer_player.addCardToHand(dealtCards[i+1]);
			playersList[next_player_index]->addCardToHand(dealtCards[i]);
			playersList[next_player_index]->setCurrentRoundNum(roundNumber);
			next_player_index = (next_player_index + 1) % total_players_num;
			playersList[next_player_index]->addCardToHand(dealtCards[i + 1]);
			playersList[next_player_index]->setCurrentRoundNum(roundNumber);
			next_player_index = (next_player_index + 1) % total_players_num;
		}
	}
	
}


void Round::printRoundDetails() {
	cout << "Round Number: " << roundNumber << endl;
	//cout << "-------------------------------------------------------------" << endl;
	if (roundNumber >= 1) {
		Deck::printDrawPile();
	}
	Deck::printDiscardPile();

	playersList[next_player_index]->printCurrentHand();
	//next_player = "Computer";
	next_player_index = (next_player_index + 1) % total_players_num;
	playersList[next_player_index]->printCurrentHand();
	next_player_index = (next_player_index + 1) % total_players_num;
	cout << endl;
	cout << endl;
	//next_player = "user";
}



void Round::roundDetails() {
	if (roundNumber >= 1) {
		dealForRound();
		printRoundDetails();
		startRound();
	}
}


void Round::startRound() {
	while (!verify_go_out) {

		cout << " --------------------------------------------" << endl;

		Deck::printDrawPile();
		Deck::printDiscardPile();
		
		playersList[next_player_index]->printCurrentHand();

		Deck::showTopDrawCard();
		//cout << endl;

		Deck::showTopDiscardCard();
		//cout << endl;
		
		cout << endl;
	
		playersList[next_player_index]->pickCard();

		next_player_index = (next_player_index + 1) % total_players_num;

		Deck::printDrawPile();
		Deck::printDiscardPile();
		cout << endl;
		Deck::showTopDrawCard();
		Deck::showTopDiscardCard();
		
		
		playersList[next_player_index]->pickCard();

		next_player_index = (next_player_index + 1) % total_players_num;
		
		verify_go_out = false;
	
	}
}

Round::~Round()
{
}
