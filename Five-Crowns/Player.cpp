#include "Player.h"



Player::Player()
{
	total_cards_in_hand = 0;
	total_wildcards_num = 0;
	total_jokers_num = 0;
	current_round_score = 0;
	
}



void Player::addCardToHand(Card card){
	total_cards_in_hand++;
	current_player_hand.push_back(card);
	string card_str = card.cardToString();
	current_player_hand_str.push_back(card_str);
	//checkWildcards(current_round_num);

}

void Player::setPlayerHand(vector<string> hand) {
	//Need to reset hand
	current_player_hand.erase(current_player_hand.begin(), current_player_hand.begin() + total_cards_in_hand);
	current_player_hand_str.erase(current_player_hand_str.begin(), current_player_hand_str.begin() + total_cards_in_hand);
	total_cards_in_hand = 0;
	total_wildcards_num = 0;
	total_jokers_num = 0; 
	current_round_score = 0;
	//current_round_num -> call set function
	vector<string>::iterator it;
	char face, suit;
	//string s_face, s_suit;
	for (it = hand.begin(); it != hand.end(); ++it) {
		face = (*it)[0];
		suit = (*it)[1];
		string s_face(1, face);
		string s_suit(1, suit);
		Card current_card = Card(s_face, s_suit);
		addCardToHand(current_card);
	}
	checkWildcards();
	checkJokercards();
	//set points

}


void Player::checkJokercards() {
	if (current_round_num != 0) {
		total_jokers_num = 0;

		for (vector<string>::iterator i = current_player_hand_str.begin(); i != current_player_hand_str.end(); ++i) {
			string current_card = *i;
			bool check_joker = checkIfJoker(current_card);
			if (check_joker) {
				total_jokers_num++;
			}
		}
	}
}

void Player::checkWildcards() {
	if (current_round_num != 0){
		//cout << endl;
		//cout << "Current roundNumber inside checkWildCards is: " << current_round_num << endl;
		total_wildcards_num = 0;

		for (vector<string>::iterator i = current_player_hand_str.begin(); i != current_player_hand_str.end(); ++i) {
			string current_card = *i;
			bool check_card = checkIfWildcard(current_card);
			if (check_card) {
				total_wildcards_num++;
			}
		}
	}
}

void Player::setCurrentRoundNum(int roundNumber) {
	current_round_num = roundNumber;
}

int Player::getCurrentRoundNum() {
	return current_round_num;
}


void Player::printCurrentHand() {
	cout << "The current player hand is: " ;
	
	vector<Card>::iterator it;
	for (it = current_player_hand.begin(); it != current_player_hand.end(); ++it) {
		it->printCard();
	}
	cout << endl;
}

void Player::pickCard() {
	cout << "Virtual function pickCard() in Player class " << endl;
}

void Player::dropCard() {
	cout << "Virtual function dropCard() in Player class " << endl;
}


void Player::decreaseHandCardNum() {
	total_cards_in_hand--;
}

int Player::getWildcardsNum() {
	return total_wildcards_num;
}


int Player::getJokersNum() {
	return total_jokers_num;
}


vector<string> Player::handToStr(vector<Card> present_hand_card) {
	vector<string> present_hand_str;
	vector<Card>::iterator it;
	for (it = present_hand_card.begin(); it != present_hand_card.end(); it++) {
		string current_card = it->cardToString();
		present_hand_str.push_back(current_card);
	}
	return present_hand_str;
}


vector<string> Player::handWithoutWildcards(vector<Card> present_hand, int &total_applicable_wildcards) {
	vector<string> present_hand_str = handToStr(present_hand);
	vector<string> temp;
	vector<string>::iterator i;
	
	for (int i = 0; i < present_hand_str.size(); i++) {
		temp.push_back(present_hand_str[i]);
	}

	for (i = temp.begin(); i != temp.end(); ) {
		string current_card = *i;
		bool check_if_joker = checkIfJoker(current_card);
		bool check_if_wildcard = checkIfWildcard(current_card);

		if (check_if_joker) {
			i = temp.erase(i);
			total_applicable_wildcards++;
		}

		else if (check_if_wildcard) {
			i = temp.erase(i);
			total_applicable_wildcards++;
		}

		else {
			++i;
		}

	}

	//cout << "returned cards without wildcards " << endl;
	return temp;

}

bool Player::checkBook(vector<Card> handToCheck) {

	int total_applicable_wildcards = 0;
	vector<string> temp = handWithoutWildcards(handToCheck, total_applicable_wildcards);

	if (temp.size() == 1) {
		return true;
	}

	vector<int> face_numbers;

	for (vector<string>::iterator i = temp.begin(); i != temp.end(); ++i) {
		string current_card = *i;
		int number = current_card.at(0) - '0';
		face_numbers.push_back(number);
	}

	sort(face_numbers.begin(), face_numbers.end());
	int total_numb = face_numbers.size();
	vector<int>::iterator it;

	it = unique(face_numbers.begin(), face_numbers.begin() + total_numb);
	face_numbers.resize(distance(face_numbers.begin(), it));
	int size_of_unique = face_numbers.size();

	if (size_of_unique <= 1) {
		return true;
	}
		
	return false;
}


bool Player::checkRun(vector<Card> current_hand_to_check) {
	
	int total_applicable_wildcards = 0;
	vector<string> temp = handWithoutWildcards(current_hand_to_check, total_applicable_wildcards);

	if (temp.size() == 1) {
		return true;
	}

	//wildcards are removed. check if all cards have the same suit.
	vector<string>::iterator i;
	vector<string> temp_suits;

	for (i = temp.begin(); i != temp.end(); ++i) {
		string current_tempandsuit = *i;
		char suit = current_tempandsuit[1];
		string s(1, suit);

		if (!(find(temp_suits.begin(), temp_suits.end(), s) != temp_suits.end())) {
			temp_suits.push_back(s);
		}
	}

	if (temp_suits.size() > 1) {
		return false;
	}

	vector<int> face_values;

	for (i = temp.begin(); i != temp.end(); ++i) {
		string current_tempandsuit = *i;
		char face = current_tempandsuit[0];
		int int_face = face - '0';
		
		if (face == 'X') {
			int_face -= 30;
		}

		if (face == 'J') {
			int_face -= 15;
		}

		if (face == 'Q') {
			int_face -= 21;
		}

		if (face == 'K') {
			int_face -= 14;
		}

		if (!(find(face_values.begin(), face_values.end(), int_face) != face_values.end())) {
			face_values.push_back(int_face);
		}
		
	}

	sort(face_values.begin(), face_values.end());


	if (face_values.size() == 1) {
		return false;
	}

	int max_diff = facesMaxDiff(face_values, face_values.size());

	if (max_diff <= (total_applicable_wildcards + 1)) {
		return true;
	}

	return false;
}



int Player::facesMaxDiff(vector<int> face_values, int vec_size) {
	
	int max_diff = face_values[1] - face_values[0];
	for (int i = 0; i < vec_size; i++) {
		for (int j = i + 1; j < vec_size; j++) {
			if (face_values[j] - face_values[i] > max_diff) {
				max_diff = face_values[j] - face_values[i];
			}
		}
	}
	return max_diff;
}


bool Player::checkIfJoker(string current_card) {
	
	if ((current_card.at(0) == 'J') && isdigit(current_card.at(1))) {
		int number = current_card.at(1) - '0';

		if (number > 0 && number < 4) {
			return true;
		}
	}

	return false;
}

bool Player::checkIfWildcard(string current_card) {
	
	if (isdigit(current_card.at(0))) {
		int number = current_card.at(0) - '0';
		if (number == (current_round_num + 2)) {
			return true;
		}
	}

	if (current_round_num == 8 && current_card.at(0) == 'X') {
		return true;
	}

	if (current_round_num == 9 && (current_card.at(0) == 'J' && !isdigit(current_card.at(1)))) {
		return true;
	}

	if (current_round_num == 10 && current_card.at(0) == 'Q') {
		return true;
	}

	if (current_round_num == 11 && current_card.at(0) == 'K') {
		return true;
	}

	return false;
}

bool Player::goOut() {
	int total_cards = current_player_hand.size();
	bool check_book;
	bool check_run;

	if (total_cards < 6) {
		check_book = checkBook(current_player_hand);
		check_run = checkRun(current_player_hand);

		if (check_book || check_run) {
			return true;
		}
		//return false;
	}

	else {
		generatePossibleCombinations();
	}

	

	return false;
}


vector<vector<Card>> Player::listBooksAndRuns(vector<vector<string>> possible_combinations) {
	
	bool checkbook, checkrun;

	for (int i = 0; i < list_books_and_runs.size(); i++) {
		list_books_and_runs[i].clear();
	}

	vector<Card> current_hand_combination;
	char face, suit;

	for (int i = 0; i < possible_combinations.size(); i++) {
		current_hand_combination.clear();
		for (int j = 0; j < possible_combinations[i].size(); j++) {
			face = possible_combinations[i][j][0];
			suit = possible_combinations[i][j][1];
			string s_face(1, face);
			string s_suit(1, suit);
			Card temp = Card(s_face, s_suit);
			current_hand_combination.push_back(temp);
		}

		checkbook = checkBook(current_hand_combination);
		checkrun = checkRun(current_hand_combination);

		if (checkbook || checkrun) {
			list_books_and_runs.push_back(current_hand_combination);
		}

	}

	cout << "Printing list of books and runs: " << endl;
	for (int i = 0; i < list_books_and_runs.size(); i++) {
		for (int j = 0; j < list_books_and_runs[i].size(); j++) {
			list_books_and_runs[i][j].printCard();
		}
		cout << endl << endl << endl;
	}

	return list_books_and_runs;
}


void Player::generatePossibleCombinations() {
	
	vector<vector<string>> possible_combinations;
	
	sort(current_player_hand_str.begin(), current_player_hand_str.end());
	
	int max_numofcards_in_combination = total_cards_in_hand;
	int min_numofcards_in_combination = 3;

	int numofcards_in_current_combination = min_numofcards_in_combination;
	int start_index_current_combination;

	while (numofcards_in_current_combination <= max_numofcards_in_combination) {
		start_index_current_combination = 0;
		

		while (start_index_current_combination <= (max_numofcards_in_combination - numofcards_in_current_combination)) {
			vector<string> current_combination;

			for (int i = start_index_current_combination; i < (numofcards_in_current_combination + start_index_current_combination); i++) {
				current_combination.push_back(current_player_hand_str[i]);
			}

			possible_combinations.push_back(current_combination);
			start_index_current_combination++; 
		}

		numofcards_in_current_combination++;

	}

	cout << "THE POSSIBLE COMBINATIONS ARE: " << endl;
	for (int i = 0; i < possible_combinations.size(); i++) {
		for (int j = 0; j < possible_combinations[i].size(); j++) {
			cout << possible_combinations[i][j] << "     ";
		}
		cout << endl;
	}

	listBooksAndRuns(possible_combinations);
}

int Player::getPlayerPoints() {
	return 0;
}

string Player::getCurrentHand() {
	string current_hand_space_sep;
	for (auto const& onecard : current_player_hand_str) {
		current_hand_space_sep = current_hand_space_sep + onecard + " ";
	}
	return current_hand_space_sep;
}

Player::~Player()
{
}
