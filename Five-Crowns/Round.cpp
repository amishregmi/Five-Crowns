#include "Round.h"



Round::Round(int roundNumber = 0)
{
	this->roundNumber = roundNumber;
	this->playerIndex = 0;
	this->playersList[0] = &human_player;
	this->playersList[1] = &computer_player;
	
}

void Round::startRound() {
	//Distribute cards to both players based on round number, and add one card to discard pile.
	vector<Card> dealtCards = deck.dealCards(roundNumber);
	vector<Card>::iterator it = dealtCards.begin();

	if (!dealtCards.empty()) {
		for (size_t i = 0; i < (dealtCards.size() - 1); i += 2) {
			human_player.addCardToHand(dealtCards[i]);
			computer_player.addCardToHand(dealtCards[i+1]);
		}
	}
	
}

void Round::printRoundDetails() {
	cout << "The current round is: ";
	cout << roundNumber << endl;

	//Initial details:
	cout << "Initial draw pile is: " << endl;
	deck.printDrawPile();

	cout << "Initial discard pile is: " << endl;
	deck.printDiscardPile();
	
	cout << "Initial human hand is: " << endl;
	human_player.printCurrentHard();

	cout << "Initial computer hand is: " << endl;
	computer_player.printCurrentHard();

	
	cout << "DEAL FOR FIRST ROUND " << endl;

	//Take this return val.


	startRound();

	cout << "New draw pile is: " << endl;
	deck.printDrawPile();

	cout << "New discard pile is: " << endl;
	deck.printDiscardPile();

	cout << "New human hand is: " << endl;
	human_player.printCurrentHard();

	cout << "New computer hand is: " << endl;
	computer_player.printCurrentHard();


}

Round::~Round()
{
}
