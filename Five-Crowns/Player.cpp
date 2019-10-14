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
	//cout << "Inside checkBook()" << endl;
	if (handToCheck.size() < 3) {
		return false;
	}
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
	//cout << "Inside checkRun" << endl;
	if (current_hand_to_check.size() < 3) {
		return false;
	}
	//cout << "Inside checkRun()" << endl;
	int total_applicable_wildcards = 0;
	vector<string> temp = handWithoutWildcards(current_hand_to_check, total_applicable_wildcards);

	if (temp.size() <= 1) {
		return true;
	}

	//Check for duplicate cards, and if so return false.

	//wildcards are removed. check if all cards have the same suit.
	vector<string>::iterator i;
	vector<string> temp_suits;
	vector<string> temp_cards;

	for (i = temp.begin(); i != temp.end(); ++i) {
		string current_tempandsuit = *i;
		char suit = current_tempandsuit[1];
		string s(1, suit);

		if (!(find(temp_cards.begin(), temp_cards.end(), current_tempandsuit) != temp_cards.end())) {
			temp_cards.push_back(current_tempandsuit);
		}

		else {
			return false;
		}

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
	//cout << "Inside goOut()" << endl;
	int total_cards = current_player_hand.size();

	hand_score = calculateSumOfCards(current_player_hand);
	//bool check_book;
	//bool check_run;

	//if (total_cards < 6) {
	//	check_book = checkBook(current_player_hand);
	//	check_run = checkRun(current_player_hand);

	//	if (check_book || check_run) {
		//	return true;
	//	}
		//return false;
	//}

	//else {
		//generatePossibleCombinations(current_player_hand_str);
		//cout << "Inside else before calling bestBookRunCombination" << endl;
		best_combination.clear();
		int score = bestBookRunCombination(current_player_hand);
		//cout << "After getting score from the bestBookRunCombination return value" << endl;
		
		cout << "LOWEST SCORE AFTER BEST COMBINATION IS: " << hand_score << endl;
	//}
		//TODO
		//Remove these cards, get list of books and runs in remaining hand and print as assemble cards.
		vector<string> assemble_remaining_bookandrun;
		vector<string> temp;
		assemble_remaining_bookandrun = current_player_hand_str;
		cout << "Best combination of remaining cards is: " << endl;
		for (auto i = recursive_bookrun_hands.begin(); i < recursive_bookrun_hands.end(); i++) {
			for (auto j = i->begin(); j < i->end(); j++) {
				cout << *j << "    ";
				temp.push_back(*j);
				assemble_remaining_bookandrun.erase(remove(assemble_remaining_bookandrun.begin(), assemble_remaining_bookandrun.end(), *j), assemble_remaining_bookandrun.end());
			}
			cout << endl;
		}

		
		//vector<vector<Card>> remaining_cards_bookrun = generatePossibleCombinations(assemble_remaining_bookandrun);
		cout << "Best combination of books and runs is: " << endl;
		//If it is present in temp, discard.
		vector<vector<string>> remaining_cards_assemble;
		/*
		for (auto i = remaining_cards_bookrun.begin(); i < remaining_cards_bookrun.end(); i++) {
			for (auto j = i->begin(); j < i->end(); j++) {
				j->printCard();
			}
			cout << endl;
		}*/
		//

		//TODO -> 9H 9H J2 JH cannot be a run
		for (auto i = best_combination.begin(); i < best_combination.end(); i++) {
			vector<string> current_bookrun_comb;
			for (auto j = i->begin(); j < i->end(); j++) {
				//cout << *j << "    ";
				if (find(temp.begin(), temp.end(), *j) != temp.end()) {
					break;
				}
				current_bookrun_comb.push_back(*j);
			}

			if (current_bookrun_comb.size() >= 3) {
				remaining_cards_assemble.push_back(current_bookrun_comb);

			}
						//cout << endl;
		}

		//TODO -> calculate sum of remaining cards, if it's equal to score, then that's the best combination
		//cout << "before last_index stuff " << endl;
		
		//int last_index = remaining_cards_assemble.size();
		//vector<string> last_hand = remaining_cards_assemble[last_index - 1];

		//cout << "Before this for " << endl;
		//for (auto j = last_hand.begin(); j < last_hand.end(); j++) {
		//	cout << *j << "   ";
		//}

		for (auto i = child_returning_smallest_sum.begin(); i < child_returning_smallest_sum.end(); i++) {
			cout << *i << "   ";
		}
		cout << endl;

		cout << endl;
	
		if (score == 0) {
			return true;
		}

	return false;
}

//TODO - > 5S 8T 9C 9T XC J1 JD. 9C 9T J1 should be on the list. 
// TODO -> 3H 7C 8C 9S XC JD KD -> JD 7C KD can be a run

int Player::bestBookRunCombination(vector<Card> current_hand) {

	//cout << "Inside bestBookRunCombination" << endl;
	vector<string> current_hand_str;
	

	for (vector<Card>::iterator it = current_hand.begin(); it < current_hand.end(); it++) {
		string card = it->cardToString();
		current_hand_str.push_back(card);
	}

	//cout << "Inside bestBookRunCombination function, the current hand is: " << endl;
	//for (auto i = current_hand.begin(); i < current_hand.end(); i++) {
	//	i->printCard();
	//}
	//cout << endl;
	//cout << endl;

	vector<vector<Card>> listof_booksandruns_currenthand = generatePossibleCombinations(current_hand_str);

	if (listof_booksandruns_currenthand.size() == 0) {
		//cout << "Inside if statement: " << endl;
		int score = calculateSumOfCards(current_hand);
		//cout << "The score is: " << score << endl;
		
		if (score <= hand_score) {		
			recursive_bookrun_hands.clear();
			recursive_bookrun_hands.push_back(current_hand_str);
			vector<string> temp;
			for (auto i = current_player_hand_str.begin(); i < current_player_hand_str.end(); i++) {
				if (!(find(current_hand_str.begin(), current_hand_str.end(), *i) != current_hand_str.end())) {
					temp.push_back(*i);
				}
			}
			if (score < hand_score) {
				best_combination.push_back(temp);
				child_returning_smallest_sum = temp;
			}
			hand_score = score;
		}

		//cout << "After comparison, hand_score is: " << hand_score << endl;
		return hand_score;
	}


	for (auto i = listof_booksandruns_currenthand.begin(); i < listof_booksandruns_currenthand.end(); i++) {
		vector<Card> hand_after_removal;
		//vector<string> recursive_caller_bookrun;
		vector<string> temp_hand_for_removal = current_hand_str;
		for (auto j = i->begin(); j < i->end(); j++) {
			//TODO -> Just remove the first occurence of an element.
			//recursive_caller_bookrun.push_back(j->cardToString());
			temp_hand_for_removal.erase(remove(temp_hand_for_removal.begin(), temp_hand_for_removal.end(), j->cardToString()), temp_hand_for_removal.end());
			//hand_after_removal.erase(remove(hand_after_removal.begin(), hand_after_removal.end(), *j), hand_after_removal.end());
		}

		//recursive_bookrun_hands.push_back(recursive_caller_bookrun);
		vector<string>::iterator it;

		for (it = temp_hand_for_removal.begin(); it < temp_hand_for_removal.end(); it++) {
			char face = (*it)[0];
			char suit = (*it)[1];
			string s_face(1, face);
			string s_suit(1, suit);
			Card current_card = Card(s_face, s_suit);
			hand_after_removal.push_back(current_card);
		}

		//cout << "About to call it self recursively" << endl;

		bestBookRunCombination(hand_after_removal);
	}

}


int Player::calculateSumOfCards(vector<Card> remaining_cards) {
	//cout << "Inside calculateSumOfCards" << endl;
	int score = 0;
	vector<Card>::iterator i;
	bool check_if_wildcard, check_if_joker;
	for (i = remaining_cards.begin(); i != remaining_cards.end(); ++i) {
		string current_tempandsuit = i->cardToString();
		check_if_wildcard = checkIfWildcard(current_tempandsuit);
		check_if_joker = checkIfJoker(current_tempandsuit);

		if (check_if_wildcard) {
			score += 20;
		}

		
		else if (check_if_joker) {
			score += 50;
		}

		else {
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

			score += int_face;
		}
	}

	//cout << "Calculated sum is " << score << endl;
	return score;
}

vector<vector<Card>> Player::generatePossibleCombinations(vector<string> current_player_hand_str) {

	//cout << "Inside generatePossibleCombinations" << endl;
	vector<vector<string>> possible_combinations;

	sort(current_player_hand_str.begin(), current_player_hand_str.end());

	//If current_player_hand_str contains X, remove it from the hand. Then, find the right position and insert again.
	vector<string> x_faces;
	vector<string> k_faces;
	vector<string> wildcardsandjokers;

	vector<string>::iterator it;

	for (it = current_player_hand_str.begin(); it != current_player_hand_str.end(); ) {
		string current_card = *it;

		if (checkIfWildcard(current_card)) {
			wildcardsandjokers.push_back(current_card);
			it = current_player_hand_str.erase(it);
		}

		else if (checkIfJoker(current_card)) {
			wildcardsandjokers.push_back(current_card);
			it = current_player_hand_str.erase(it);
		}

		else {
			if (current_card.at(0) == 'X') {
				x_faces.push_back(current_card);
				it = current_player_hand_str.erase(it);
			}

			else if (current_card.at(0) == 'K') {
				k_faces.push_back(current_card);
				it = current_player_hand_str.erase(it);
			}
			else {
				++it;
			}
		}
	
	}

	//cout << "Hand after removing X's and K's is " << endl;
	
	//cout << endl;

	//cout << "After printing hand without X and K" << endl;
	sort(x_faces.begin(), x_faces.end());
	sort(k_faces.begin(), k_faces.end());

	//cout << "After sorting " << endl;
	//find first position of either J or Q.
	int first = 50;

	for (auto i = current_player_hand_str.begin(); i < current_player_hand_str.end(); i++) {
		//if (!checkIfJoker(*i)) {
		string current_card = *i;
		//cout << "Inside for loop " << endl;
			if (current_card.at(0) == 'J' || current_card.at(0) == 'Q') {
				//cout << "Inside J or Q found " << endl;
				auto finder = find(current_player_hand_str.begin(), current_player_hand_str.end(), *i);
				if (finder == current_player_hand_str.end()) {
					//cout << "Some error " << endl;
				}
				else {
					auto index = distance(current_player_hand_str.begin(), finder);
					//cout << "Found at index " << index << endl;
					if (index < first) {
						first = index;
					}

				}
			}
		//}
	}

	for (auto i = x_faces.begin(); i < x_faces.end(); i++) {
		if (first == 50) {
			current_player_hand_str.push_back(*i);
		}
		else {
			current_player_hand_str.insert(current_player_hand_str.begin() + first, *i);
			first++;
		}
	}


	for (auto i = k_faces.begin(); i < k_faces.end(); i++) {
		current_player_hand_str.push_back(*i);
	}


	/*
	cout << "After sorting, the hand without wildcards and jokers is: " << endl;
	for (auto i = current_player_hand_str.begin(); i < current_player_hand_str.end(); i++) {
		cout << *i << "    ";
	}
	cout << endl; */

	int max_numofcards_in_combination = current_player_hand_str.size();
	int min_numofcards_in_combination = 3;

	if (wildcardsandjokers.size() == 1) {
		min_numofcards_in_combination--;
	}

	else if (wildcardsandjokers.size() >= 2) {
		min_numofcards_in_combination -= 2; 
	}

	int numofcards_in_current_combination = min_numofcards_in_combination;
	int start_index_current_combination;


	//cout << "Inside while 1 " << endl;
	while (numofcards_in_current_combination <= max_numofcards_in_combination) {
		
		//cout << "Inside outer while " << endl;
		start_index_current_combination = 0;

		//cout << "before while 2 " << endl;
		while (start_index_current_combination <= (max_numofcards_in_combination - numofcards_in_current_combination)) {
			//cout << "Inside while 2 " << endl;
			//cout << "Inside inner while " << endl;
			vector<string> current_combination;
			
			for (int i = start_index_current_combination; i < (numofcards_in_current_combination + start_index_current_combination); i++) {
				//cout << "Inside for " << endl;
				//cout << "Line 642" << endl;
				if (i < current_player_hand_str.size()) {
					current_combination.push_back(current_player_hand_str[i]);
				}
			}
			//cout << "Line 647" << endl;
			possible_combinations.push_back(current_combination);
			start_index_current_combination++;
		}

		numofcards_in_current_combination++;
		//cout << "Line 653" << endl;
	}

	/*
	 */
	/*
	for (int i = 0; i < possible_combinations.size(); i++) {
	for (int j = 0; j < possible_combinations[i].size(); j++) {
	cout << possible_combinations[i][j] << "     ";
	}
	cout << endl;
	} */

	vector<vector<string>> copy_possible_combinations;
	copy_possible_combinations = possible_combinations;
	//cout << "Outside while  " << endl;
	//cout << "Outside while " << endl;
	for (auto i = copy_possible_combinations.begin(); i < copy_possible_combinations.end(); i++) {
		//cout << "Line 670" << endl;
		//cout << "Inside for 1" << endl;
		//for (auto j = i->begin(); j < i->end(); j++) {
		vector<string> temp = *i;
		for (auto j = wildcardsandjokers.begin(); j < wildcardsandjokers.end(); j++) {
			//cout << "Inside second for " << endl;
			temp.push_back(*j);
			possible_combinations.push_back(temp);
		}
	}

	/*
	cout << "THE POSSIBLE COMBINATIONS ARE: " << endl;

	for (auto i = possible_combinations.begin(); i < possible_combinations.end(); i++) {
		for (auto j = i->begin(); j < i->end(); j++) {
			cout << *j << "    ";
		}
		cout << endl;
	} */
	
	//cout << "Line 692 " << endl;
	return listBooksAndRuns(possible_combinations);
}

//TODO
//currently, JD JT 7S, JD JT 7S J2 but not JD JT J2


//TODO->
/*
3S 4C 4T 5S XC JS, wildcard -> 7S
listofbooks and runs -> 4C 4T 7S but not 3S 7S 5S

*/
vector<vector<Card>> Player::listBooksAndRuns(vector<vector<string>> possible_combinations) {
	
	//cout << "Inside listBooksAndRuns" << endl;
	bool checkbook, checkrun;
	vector<vector<Card>> list_books_and_runs;

	//cout << "Inside listBooksAndRuns" << endl;
	//cout << "Before clear " << endl;
	for (int i = 0; i < list_books_and_runs.size(); i++) {
		list_books_and_runs[i].clear();
	}

	//vector<Card> current_hand_combination;
	char face, suit;

	//cout << "Before for loop " << endl;

	//ERROR INSIDE FOR LOOP
	for (auto i = possible_combinations.begin(); i < possible_combinations.end(); i++) {
		vector<Card> current_hand_combination;
		//cout << "Before inside for " << endl;
		for (auto j = i->begin(); j < i->end(); j++) {
			face = (*j)[0];
			suit = (*j)[1];
			string s_face(1, face);
			string s_suit(1, suit);
			Card temp = Card(s_face, s_suit);
			current_hand_combination.push_back(temp);
		}
		//cout << "After inside for " << endl;
		checkbook = checkBook(current_hand_combination);
		checkrun = checkRun(current_hand_combination);
		if (checkbook || checkrun) {
			list_books_and_runs.push_back(current_hand_combination);
		}
		//cout << "After if " << endl;
	}
	/*
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

		

	}
	*/
	//ERROR IS BEFORE PRINTING.

	/*
	cout << "Printing list of books and runs: " << endl;
	for (auto i = list_books_and_runs.begin(); i < list_books_and_runs.end(); i++) {
		for (auto j = i->begin(); j < i->end(); j++) {
			j->printCard();
		}
		cout << endl;
	}*/

	//cout << "Printed and returned " << endl;

	return list_books_and_runs;
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
