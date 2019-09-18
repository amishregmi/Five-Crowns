#include "Round.h"

string Round::next_player;

Round::Round(int roundNumber = 0)
{
	this->roundNumber = roundNumber;
	//Determine next_player_index by coin toss.
	this->next_player_index = 0;
	this->total_players_num = 2;
	this->verify_go_out_first = false;
	this->verify_go_out_second = false;
	cout << "Round Number: " << roundNumber << endl;
	if (roundNumber == 1) {
		string toss_val = coinToss();

		if (toss_val == "Human") {
			this->playersList[0] = &human_player;
			this->playersList[1] = &computer_player;
			this->player_names[0] = "Human";
			this->player_names[1] = "Computer";
		}

		else {
			this->playersList[0] = &computer_player;
			this->playersList[1] = &human_player;
			this->player_names[0] = "Computer";
			this->player_names[1] = "Human";
		}
	}

	else {
		//Don't change -> next_player if go out successful
		if (this->next_player == "Human") {
			this->playersList[0] = &human_player;
			this->playersList[1] = &computer_player;
			this->player_names[0] = "Human";
			this->player_names[1] = "Computer";
		}

		else {
			this->playersList[0] = &computer_player;
			this->playersList[1] = &human_player;
			this->player_names[0] = "Computer";
			this->player_names[1] = "Human";
		}
	}
}


string Round::coinToss() {
	cout << endl;
	cout << "Tossing coin for first round " << endl;
	srand(time(NULL));
	int toss_val = rand() % 2;
	cout << "The coin toss value is: " << toss_val << endl;
	int human_call;
	cout << "Enter 0 for heads and 1 for tails: ";
	cin >> human_call;
	if (human_call != 0 && human_call != 1) {
		do {
			cout << "Invalid input. Please enter 0 or 1: ";
			cin >> human_call;
		} while (human_call != 0 && human_call != 1);
	}

	if (human_call == toss_val) {
		cout << "Human won the toss and is going first " << endl;
		return "Human";
	}

	else {
		cout << "Human lost the toss computer is going first " << endl;
		return "Computer";
	}

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
	
	Deck::printDrawPile();
	Deck::printDiscardPile();
	
	cout << "Playing: " << player_names[next_player_index] << "    ";
	playersList[next_player_index]->printCurrentHand();

	Deck::showTopDrawCard();
	Deck::showTopDiscardCard();
	cout << endl;
}



void Round::roundDetails() {

	if (roundNumber >= 1) {
		dealForRound();
		startRound();
	}
}


void Round::startRound() {

	while (!verify_go_out_first && !verify_go_out_second) {

		cout << " --------------------------------------------" << endl;
		printRoundDetails();

		playersList[next_player_index]->pickCard();
		verify_go_out_first = playersList[next_player_index]->goOut();
		
		if (verify_go_out_first) {
			cout << "Player " << player_names[next_player_index] << " went out" << endl;
		}
		
		next_player_index = (next_player_index + 1) % total_players_num;

		printRoundDetails();
		
		playersList[next_player_index]->pickCard();
		verify_go_out_second = playersList[next_player_index]->goOut();

		if (verify_go_out_second) {
			cout << "Player " << player_names[next_player_index] << " went out" << endl;
		}

		next_player_index = (next_player_index + 1) % total_players_num;

		if (verify_go_out_first && !verify_go_out_second) {
			//calculate points of second player.
			cout << "Calculating points for player " << player_names[next_player_index+1] << endl;
		}

		if (!verify_go_out_first && verify_go_out_second) {
			//calculate points of first player
			cout << "Calculating points for player: " << player_names[next_player_index] << endl;
			next_player_index = (next_player_index + 1) % total_players_num;
		}

	}
}

Round::~Round()
{
}
