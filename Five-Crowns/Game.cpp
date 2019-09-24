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
		human_player_points = 0;
		computer_player_points = 0;
		round_number = 1;
		Deck::Deck();
		callRound(round_number);
	}
}

void Game::callRound(int round_number = 0) {
	//Main game loop
	while (round_number <= 13) {
		Round round(round_number);
		round.roundDetails();
		round_number++;
	}
}

void Game::extractDetailsFromFile(string file_name) {
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
