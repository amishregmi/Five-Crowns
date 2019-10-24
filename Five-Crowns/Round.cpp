#include "Round.h"


//DISCARDED 5C EXCEPT RECOMMENDATION

/* *********************************************************************
Function Name: Round
Purpose: Constructor for the Round class.
Parameters:
	roundNumber, the integer of the current round number.
	human_player_ptr, a pointer to a human player object.
	computer_player_ptr, a pointer to a computer player object
	next_player_name, a string containing the next player
	read_from_file, a boolean set to true when user wants to read a serialized file
Assistance Received: none
********************************************************************* */

Round::Round(int roundNumber, Human* human_player_ptr, Computer* computer_player_ptr, string next_player_name, bool read_from_file){

	this->readfromfile = read_from_file;
	this->human_player = *human_player_ptr;
	this->computer_player = *computer_player_ptr;
	this->roundNumber = roundNumber;
	this->next_player_index = 0;
	this->total_players_num = 2;
	this->verify_go_out_first = false;
	this->verify_go_out_second = false;
	cout << endl;
	cout << endl;
	cout << "Round Number: " << roundNumber << endl;
	if (roundNumber == 1) {
		if (next_player_name == "Human") {
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
		if (next_player_name == "Human") {
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

/* *********************************************************************
Function Name: dealForRound
Purpose: To deal the cards from draw pile to the players for the current round
Parameters:
	None
Return Value: None
Local Variables:
	dealtCards, a vector of cards containing the cards to deal to the two players
	it, an iterator for vector of cards
Assistance Received: none
********************************************************************* */

void Round::dealForRound() {
	vector<Card> dealtCards = Deck::dealCards(roundNumber);
	vector<Card>::iterator it = dealtCards.begin();

	if (!dealtCards.empty()) {
		for (size_t i = 0; i < (dealtCards.size() - 1); i += 2) {
			playersList[next_player_index]->addCardToHand(dealtCards[i]);
			playersList[next_player_index]->setCurrentRoundNum(roundNumber);
			next_player_index = (next_player_index + 1) % total_players_num;
			playersList[next_player_index]->addCardToHand(dealtCards[i + 1]);
			playersList[next_player_index]->setCurrentRoundNum(roundNumber);
			next_player_index = (next_player_index + 1) % total_players_num;
		}
	}
	
}

/* *********************************************************************
Function Name: printRoundDetails
Purpose: To print details of the current round, the drawPile, the discardPile, the round number, the next player, the top draw pile card and the top discard pile card.
Parameters:
	None
Return Value: None
Local Variables:
	None
Assistance Received: none
********************************************************************* */

void Round::printRoundDetails() {
	cout << endl;
	cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	Deck::printDrawPile();
	Deck::printDiscardPile();
	cout << " -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- " << endl;
	cout << "Round: " << roundNumber << endl;
	cout << "Playing: " << player_names[next_player_index] << "    ";
	playersList[next_player_index]->printCurrentHand();
	Deck::showTopDrawCard();
	Deck::showTopDiscardCard();
	
	cout << endl;
}

/* *********************************************************************
Function Name: roundDetails
Purpose: Function to arrange for the round to start
Parameters:
	None
Return Value: None
Local Variables:
	None
Assistance Received: none
********************************************************************* */

void Round::roundDetails() {
	if (roundNumber >= 1) {
		if (!readfromfile) {
			dealForRound();
		}
		startRound();
	}
}

/* *********************************************************************
Function Name: saveGame
Purpose: Function to save the state of the game to the serialized file
Parameters:
	None
Return Value: None
Local Variables:
	saved_file, an ofstream object
Assistance Received: none
********************************************************************* */

void Round::saveGame() {
	ofstream saved_file;
	saved_file.open(SAVED_GAME);
	saved_file << "Round: " << roundNumber << "\n\n";
	saved_file << "Computer: " << "\n";
	saved_file << "    Score: " <<  Game::getComputerTotalPoints() << "\n";
	saved_file << "    Hand: " << computer_player.getCurrentHand() << "\n\n";
	saved_file << "Human: " << "\n";
	saved_file << "    Score: " << Game::getHumanTotalPoints() << "\n";
	saved_file << "    Hand: " << human_player.getCurrentHand() << "\n\n";
	saved_file << "Draw Pile: " << Deck::getCurrentDrawPile() << "\n\n";
	saved_file << "Discard Pile: " << Deck::getCurrentDiscardPile() << "\n\n";
	saved_file << "Next Player: " << player_names[next_player_index] << "\n";
	exit(0);
}

/* *********************************************************************
Function Name: menuOptions
Purpose: Function to display menu options and call action according to user input
Parameters:
	None
Return Value: None
Local Variables:
	input_c, a character to get the user input
Assistance Received: none
********************************************************************* */

void Round::menuOptions() {
	cout << "----------------------------------------------------------------------------------------[[**MENU**]]------------------------------------------------------------------------------------" << endl;
	cout << "1. Save the game" << endl;
	cout << "2. Make a move" << endl;
	if (player_names[next_player_index] == "Human") {
		cout << "3. Ask for help" << endl;
	}
	cout << "4. Quit the game" << endl;
	cout << " --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

	char input_c;
	cout << "Enter your choice from the above numbers: ";
	cin >> input_c;

	int input = input_c - '0';

	if (input != 1 && input != 2 && input != 4 && !(player_names[next_player_index] == "Human" && input == 3)) {
		do {
			cout << "Invalid input. Please enter a valid number ";
			cin >> input_c;
			input = input_c - '0';
		} while (input != 1 && input != 2 && input != 4 && !(player_names[next_player_index] == "Human" && input == 3));
	}

	if (input == 1) {
		saveGame();
	}

	if (input == 2) {
		playersList[next_player_index]->pickCard();
	}

	if (player_names[next_player_index] == "Human" && input == 3) {
		playersList[next_player_index]->pickCardHelp();
		playersList[next_player_index]->pickCard();
	}

	if (input == 4) {
		exit(0);
	}
}

/* *********************************************************************
Function Name: startRound
Purpose: Function to start the round, let the players play and end when one of the players go out
Parameters:
	None
Return Value: None
Local Variables:
	None
Assistance Received: none
********************************************************************* */

void Round::startRound() {

	while (!verify_go_out_first && !verify_go_out_second) {
		//cout << " -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
		printRoundDetails();
		menuOptions();
		verify_go_out_first = playersList[next_player_index]->goOut();
				
		if (verify_go_out_first) {
			cout << "Player " << player_names[next_player_index] << " went out" << endl;
			playersList[next_player_index]->printAvailableBooksandRuns();
		}
		
		next_player_index = (next_player_index + 1) % total_players_num;
		printRoundDetails();
		menuOptions();

		verify_go_out_second = playersList[next_player_index]->goOut();

		if (verify_go_out_second) {
			cout << "Player " << player_names[next_player_index] << " went out" << endl;
			playersList[next_player_index]->printAvailableBooksandRuns();
		}

		next_player_index = (next_player_index + 1) % total_players_num;

		if (verify_go_out_first && !verify_go_out_second) {
			cout << endl;
			cout << "The points for player " << player_names[next_player_index+1] << " is ";
			cout << playersList[next_player_index + 1]->getHandScore() << endl;
			playersList[next_player_index + 1]->printAvailableBooksandRuns();		
		}

		if (!verify_go_out_first && verify_go_out_second) {
			printRoundDetails();
			menuOptions();
			cout << endl;
			playersList[next_player_index]->printAvailableBooksandRuns();
			cout << "The points for player " << player_names[next_player_index] << " is ";
			verify_go_out_first = playersList[next_player_index]->goOut();
			if (verify_go_out_first) {
				cout << "0 since Player " << player_names[next_player_index] << " went out" << endl;
			}
			else {
				cout << playersList[next_player_index]->getHandScore() << endl;
			}
			next_player_index = (next_player_index + 1) % total_players_num;
		}
	}

}

/* *********************************************************************
Function Name: getNextPlayer
Purpose: Function that returns the next player
Parameters:
	None
Return Value: a string containing the next player
Local Variables:
	None
Assistance Received: none
********************************************************************* */

string Round::getNextPlayer() {
	return player_names[next_player_index];
}

/* *********************************************************************
Function Name: getHumanScore
Purpose: Function that returns the human player score
Parameters:
	None
Return Value: an integer containing the current score of the human player
Local Variables:
	None
Assistance Received: none
********************************************************************* */

int Round::getHumanScore() {
	return human_player.getHandScore();
}

/* *********************************************************************
Function Name: getComputerScore
Purpose: Function that returns the computer player score
Parameters:
	None
Return Value: an integer containing the current score of the computer player
Local Variables:
	None
Assistance Received: none
********************************************************************* */

int Round::getComputerScore() {
	return computer_player.getHandScore();
}

//Default destructor

Round::~Round()
{
}
