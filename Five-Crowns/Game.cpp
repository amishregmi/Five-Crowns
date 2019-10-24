#include "Game.h"

//Initializing static members.

int Game::human_player_points;
int  Game::computer_player_points;

/* *********************************************************************
Function Name: Game
Purpose: Constructor for the Game class. Gives the option to either read from file or start a new game and calls method to set up a round.
Local Variables:
	input, a char to check if user wants to read from serialized file or start a new game
	file_name, a string containing name of the file user wants to load the game from
	game_progress, ifstream to load the serialization file
Assistance Received: none
********************************************************************* */

Game::Game()
{
	char input;
	cout << "Welcome to the game: ";
	cout << "Enter y to load a saved game. Enter any other key otherwise: ";
	cin >> input;
	

	if (input == 'Y' || input == 'y') {
		string file_name;
		cout << "Please enter the name of the file: ";
		cin >> file_name;
		ifstream game_progress;
		game_progress.open(file_name);
		if (game_progress.fail()) {
			do {
				cout << "Invalid input. Please enter correct file name and path: ";
				cin >> file_name;
				game_progress.open(file_name);

			} while (game_progress.fail());
		}
		extractDetailsFromFile(file_name);
	}

	else {
		read_from_file = false;
		human_player_points = 0;
		computer_player_points = 0;
		round_number = 1;
	}

	callRound();
}

/* *********************************************************************
Function Name: callRound
Purpose: The main game loop. Call the round based on either new game settings or settings loaded from serialized file and display winner at the end.
Local Variables:
	toss_winner, string containing winner of coin toss for first round
	first_went_out, a string containing the first player to go out, which is the first player in next round.
Assistance Received: none
********************************************************************* */

void Game::callRound() {
	
	if (round_number == 1 && !read_from_file) {
		string toss_winner = coinToss();
		
		if (toss_winner == "Human") {
			this->next_player = "Human";
		}
		else {
			this->next_player = "Computer";
		}
	}

	while (round_number <= 11) {

		Round round(round_number, &human, &computer, next_player, read_from_file);
		round.roundDetails();
		
		cout << "***************************************************************************************************" << endl;
		cout << "After round: " << round_number << endl;
		human_player_points += round.getHumanScore();
		computer_player_points += round.getComputerScore();

		cout << "Human score is: " << human_player_points << " and Computer score is: " << computer_player_points << endl;		
		cout << "***************************************************************************************************" << endl;
		string first_went_out = round.getNextPlayer();

		if (first_went_out == "Human") {
			next_player = "Human";
		}
		else {
			next_player = "Computer";
		}
		
		human.clearCurrentHand();
		computer.clearCurrentHand();
		read_from_file = false;

		round_number++;
	}

	cout << " -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- " << endl;
	cout << " -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- " << endl;
	cout << "After all rounds, the human score is: " << human_player_points << endl;
	cout << "After all rounds, the computer score is: " << computer_player_points << endl;

	if (human_player_points < computer_player_points) {
		cout << "Human player won the game" << endl;
	}

	else if (human_player_points > computer_player_points) {
		cout << "Computer player won the game " << endl;
	}

	else {
		cout << "The game ended in a tie " << endl;
	}

	cout << "********************************************************************************[[[[END]]]]********************************************************************************************" << endl;
}

/* *********************************************************************
Function Name: extractDetailsFromFile
Purpose: To extract required details from serialized file before calling round.
Parameters:
	file_name, a string containing the name of the file to read from.
Local Variables:
	load_details, ifstream object to open the file into
	oneline, every line of the file
	strm, istringstream object to extract the words of the file
	word, extracted invidiual words from the file
Assistance Received: none
********************************************************************* */

void Game::extractDetailsFromFile(string file_name) {
	read_from_file = true;
	ifstream load_details;
	string oneline;
	load_details.open(file_name);
	while (getline(load_details, oneline)) {

		//cout << oneline << endl;
		istringstream strm(oneline);
		string word;

		strm >> word;

		//cout << "Extracting from file" << endl;

		if (word == "Round:") {
			strm >> word;
			round_number = stoi(word);
			//cout << "Round Number is: " << round_number << endl;
		}

		else if (word == "Draw") {
			string drawpilefile = oneline.substr(oneline.find_first_of(":") + 1);
			vector<string> draw_pile_cards = extract_card_str(drawpilefile);
			reverse(draw_pile_cards.begin(), draw_pile_cards.end());
			Deck::setDrawPile(draw_pile_cards);
		}

		else if (word == "Discard") {
			string discardpilefile = oneline.substr(oneline.find_first_of(":") + 1);
			vector<string> discard_pile_cards = extract_card_str(discardpilefile);
			reverse(discard_pile_cards.begin(), discard_pile_cards.end());
			Deck::setDiscardPile(discard_pile_cards);
		}

		else if (word == "Next") {
			string next_player_txt = oneline.substr(oneline.find_first_of(":") + 1);
			vector<string> next_playerr = extract_card_str(next_player_txt);
			this->next_player = next_playerr[0];
		}

		else if (word == "Human:" || word == "Computer:") {
			string indented_line, values, player_hand;
			vector<string> cards_str;
			int player_score;
			
			for (int i = 0; i < 2; i++) {
				getline(load_details, indented_line); 
				istringstream strm1(indented_line);
				strm1 >> values;

				if (values == "Score:") {
					strm1 >> values;
					player_score = stoi(values);
				}

				else if (values == "Hand:") {
					player_hand = indented_line.substr(indented_line.find_first_of(":") + 1);
					//cout << "Player_Hand is: " << player_hand << endl;
					cards_str = extract_card_str(player_hand);
				}
			}

			if (word == "Human:") {
				//Player(vector<string>, int, int); 
				human.setPlayerHand(cards_str);
				human.setCurrentRoundNum(round_number);
				human_player_points = player_score;
			}

			else if (word == "Computer:") {
				computer.setPlayerHand(cards_str);
				computer.setCurrentRoundNum(round_number);
				computer_player_points = player_score;
			}
		}
	}
	cout << "Human score is: " << human_player_points << endl;
	cout << "Computer score is: " << computer_player_points << endl;
}

/* *********************************************************************
Function Name: extract_card_str
Purpose: To extract individual cards from a string containing space separated string representation of cards
Parameters:
hand, a string containing the card values space seperated
Return Value: vector of strings where each string is a representation of a card
Local Variables:
cards, a vector of string containing string representation of the cards
word, a string containing one card
iss, a stringstream object where the string containing all cards is loaded
Assistance Received: none
********************************************************************* */

vector<string> Game::extract_card_str(string hand) {
	vector<string> cards;
	string word;
	stringstream iss(hand);
	while (iss >> word) {
		cards.push_back(word);
	}
	return cards;
}

/* *********************************************************************
Function Name: coinToss
Purpose: To toss the coin when starting a new game
Return Value: a string containing the name of the player who won the coin toss
Local Variables:
toss_val, a random integer either 0 or 1
human_calll, a char of user input of coin toss guess
human_call, integer conversion of char human input
Assistance Received: none
********************************************************************* */

string Game::coinToss() {
	cout << endl;
	cout << "Tossing coin for first round " << endl;
	srand(time(NULL));
	int toss_val = rand() % 2;
	//cout << "The coin toss value is: " << toss_val << endl;
	char human_calll;
	int human_call;
	cout << "Enter 0 for heads and 1 for tails: ";
	cin >> human_calll;
	human_call = human_calll - '0';

	if (human_call != 0 && human_call != 1) {
		do {
			cout << "Invalid input. Please enter 0 or 1: ";
			cin >> human_calll;
			human_call = human_calll - '0';
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

/* *********************************************************************
Function Name: getComputerTotalPoints
Purpose: To returns the total points of computer player when saving details from round class during serialization
Return Value: The total computer player points, an integer value
Assistance Received: none
********************************************************************* */

const int Game::getComputerTotalPoints() {
	return computer_player_points;
}

/* *********************************************************************
Function Name: getHumanTotalPoints
Purpose: To returns the total points of human player when saving details from round class during serialization
Return Value: The total human player points, an integer value
Assistance Received: none
********************************************************************* */

const int Game::getHumanTotalPoints() {
	return human_player_points;
}


//Default destructor

Game::~Game()
{
}
