#include "Game.h"



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
		//game_progress(file_name);
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

void Game::callRound() {
	//Main game loop
	round_number = 5;

	if (round_number == 1 && !read_from_file) {
		string toss_winner = coinToss();
		
		if (toss_winner == "Human") {
			this->next_player = "Human";
		}
		else {
			this->next_player = "Computer";
		}
	}


	//while (round_number <= 13) {
		Round round(round_number, &human, &computer, "Human", read_from_file);
		//cout << "Calling roundDetails() function from Game" << endl;
		round.roundDetails();
	//	round_number++;
	//}
}

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
	
}


string Game::coinToss() {
	cout << endl;
	cout << "Tossing coin for first round " << endl;
	srand(time(NULL));
	int toss_val = rand() % 2;
	//cout << "The coin toss value is: " << toss_val << endl;
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


vector<string> Game::extract_card_str(string hand) {
	vector<string> cards;
	string word;
	stringstream iss(hand);
	while (iss >> word) {
		cards.push_back(word);
	}
	return cards;
}

Game::~Game()
{
}
