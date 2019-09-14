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
			next_player_index = (next_player_index + 1) % total_players_num;
			playersList[next_player_index]->addCardToHand(dealtCards[i + 1]);
			next_player_index = (next_player_index + 1) % total_players_num;
		}
	}
	
}

int Round::getRoundNumber() {
	return roundNumber;
}

void Round::printRoundDetails() {
	cout << "The current round number is: " << roundNumber << endl;
	cout << "-----------------------------------" << endl;
	Deck::printDrawPile();
	Deck::printDiscardPile();

	playersList[next_player_index]->printCurrentHand();
	//next_player = "Computer";
	next_player_index = (next_player_index + 1) % total_players_num;
	playersList[next_player_index]->printCurrentHand();
	next_player_index = (next_player_index + 1) % total_players_num;
	//next_player = "user";
}



void Round::roundDetails() {
	printRoundDetails();
	dealForRound();
	printRoundDetails();
	startRound();
}

void Round::startRound() {
	while (!verify_go_out) {
		
		Deck::showTopDiscardCard();
		cout << endl;
		Deck::showTopDrawCard();
		
		playersList[next_player_index]->pickCard();

		next_player_index = (next_player_index + 1) % total_players_num;
		verify_go_out = true;
	
	}
}

Round::~Round()
{
}
