#include "Player.h"

/* *********************************************************************
Function Name: Player
Purpose: Constructor for the Player class. Initialize all member variables
Parameters:
	None
Assistance Received: none
********************************************************************* */

Player::Player()
{
	total_cards_in_hand = 0;
	total_wildcards_num = 0;
	total_jokers_num = 0;
	current_player_hand.clear();
	current_player_hand_str.clear();
}

/* *********************************************************************
Function Name: addCardToHand
Purpose: To add a card object to the current player's hand
Parameters:
	card, a card object to be added to hand
Return Value: None
Local Variables:
	card_str, a string representation of the card object
Assistance Received: none
********************************************************************* */

void Player::addCardToHand(Card card){
	total_cards_in_hand++;
	current_player_hand.push_back(card);
	string card_str = card.cardToString();
	current_player_hand_str.push_back(card_str);
}

/* *********************************************************************
Function Name: setPlayerHand
Purpose: To set the current player's hand
Parameters:
	hand, a vector of strings containing string representation of card objects
Return Value: None
Local Variables:
	face, a character of the face of the card
	suit, a character of the suit of the card
	s_face, string of face of card
	s_suit, string of suit of the card
	current_card, the card object
Assistance Received: none
********************************************************************* */

void Player::setPlayerHand(vector<string> hand) {
	//Need to reset hand
	current_player_hand.erase(current_player_hand.begin(), current_player_hand.begin() + total_cards_in_hand);
	current_player_hand_str.erase(current_player_hand_str.begin(), current_player_hand_str.begin() + total_cards_in_hand);
	total_cards_in_hand = 0;
	total_wildcards_num = 0;
	total_jokers_num = 0; 
	vector<string>::iterator it;
	char face, suit;
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
}

/* *********************************************************************
Function Name: checkJokercards
Purpose: To find and set the number of jokers in the current hand
Parameters:
	None
Return Value: None
Local Variables:
	current_card, a string representing a card object
	check_joker, a boolean set to true if the current string of card object is joker
Assistance Received: none
********************************************************************* */

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

/* *********************************************************************
Function Name: checkWildCards
Purpose: To find and set the number of wildcards in the current hand
Parameters:
	None
Return Value: None
Local Variables:
	current_card, a string representing a card object
	check_card, a boolean set to true if the current string of card object is wildcard
Assistance Received: none
********************************************************************* */

void Player::checkWildcards() {
	if (current_round_num != 0){
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

//Function to set the current round number in player class

void Player::setCurrentRoundNum(int roundNumber) {
	current_round_num = roundNumber;
}

/* *********************************************************************
Function Name: printCurrentHand
Purpose: To print the current player's hand to the console
Parameters:
	None
Return Value: None
Local Variables:
	it, an iterator for the vector of cards of current hand
Assistance Received: none
********************************************************************* */

void Player::printCurrentHand() {
	cout << "The current player hand is: " ;
	
	vector<Card>::iterator it;
	for (it = current_player_hand.begin(); it != current_player_hand.end(); ++it) {
		it->printCard();
	}
	cout << endl;
}


//Virtual function pickCard in player hand overriden in human class

void Player::pickCardHelp() {
	cout << "Virtual function pickCardHelp() in Player class " << endl;
}

//Virtual function pickCard in player hand overriden in computer and human class

void Player::pickCard() {
	cout << "Virtual function pickCard() in Player class " << endl;
}

//virtual function dropCard overridden in computer and human class.

void Player::dropCard() {
	cout << "Virtual function dropCard() in Player class " << endl;
}

/* *********************************************************************
Function Name: handToStr
Purpose: To get a vector of strings representation of any hand passed as argument
Parameters:
	present_hand_card, the hand for which string representation of vector is required
Return Value: a vector of strings representing the hand
Local Variables:
	present_hand_str, a vector of strings that is returned
	current_card, a string to represent each individual card in the hand inside the loop
Assistance Received: none
********************************************************************* */

vector<string> Player::handToStr(vector<Card> present_hand_card) {
	vector<string> present_hand_str;
	vector<Card>::iterator it;
	for (it = present_hand_card.begin(); it != present_hand_card.end(); it++) {
		string current_card = it->cardToString();
		present_hand_str.push_back(current_card);
	}
	return present_hand_str;
}

/* *********************************************************************
Function Name: handWithoutWildcards
Purpose: To get a vector of strings representation the hand passed in argument without its wildcards and jokers
Parameters:
	present_hand, vector of cards from where wildcards and jokers are to be taken out	
	total_applicable_wildcards, an integer passed by reference which is set to the total number of wildcards and jokers found in the hand
Return Value: a vector of strings representing the hand without wildcards and jokers
Local Variables:
	present_hand_str, string representation of the vector of card objects passed
	temp, a vector of strings where each string is pushed and checked whether it is wildcard or joker
	check_if_joker, a boolean set to true if current card is a joker
	check_if_wildcard, a boolean set to true if current hand is a wildcard
Algorithm:
	1) For every card in the hand passed, check if it's a wildcard or a joker
	2) If so, remove it from the hand, add it to a vector of strings and return the value. Also, increase total_applicable_wildcards passed by reference
Assistance Received: none
********************************************************************* */

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
	return temp;
}

/* *********************************************************************
Function Name: checkBook
Purpose: To check if the vector of cards passed as argument forms a book
Parameters:
	handToCheck, a vector of cards 
Local Variables:
	temp, a vector of strings that contains the hand passed minus wildcards and jokers
	face_numbers, a vector of integers that holds the face values of cards in temp
	total_numb, int size of face_numbers
	size_of_unique, an integer containing the number of unique values in face_numbers
Algorithm:
	1) If the handToCheck passed as parameter is less than 3, return false.
	2) Get the hand without wildcards. If the size of this is 1, return True.
	3) For every card in hand without wildcards, extract it's face value and push to a vector of integers [face_numbers]
	4) Find the unique elements in face_numbers and resize it accordingly to just have the unique elements.
	5) If size is less than or equal to 1, it's a book and return true. Else, return false.
Assistance Received: none
********************************************************************* */

bool Player::checkBook(vector<Card> handToCheck) {
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

/* *********************************************************************
Function Name: checkRun
Purpose: To check if the vector of cards passed as argument forms a run
Parameters:
	current_hand_to_check, a vector of cards
Local Variables:
	temp, a vector of strings that contains the hand passed minus wildcards and jokers
	temp_suits, a vector of strings containing the suits of the cards
	temp_cards, a vector of strings containing the cards without wildcards or jokers
	current_tempandsuit, string representing a card object
	suit, the suit character
	s, string casting of the suit character
	face_values, a vector of integers containing the face values in temp.
	max_diff, an integer containing the difference between the cards of the hand containing the samllest and the largest face value after elimination of wildcards and jokers
Algorithm:
	1) If size of hand passed is less than 3, return false. Needs atleast 3 cards for a run.
	2) Get the string representation of the hand of Cards without wildcards or jokers and get the sum of total number of wildcards and jokers in the hand. Save it in temp.
	3) If size of temp is less than or equal to 1, return true. A hand with atleast 3 elements where number of wildcards is equal to or greater than 2 forms a run.
	4) For every card in temp, check if the card already exists in temp_cards. If so, return false. A run cannot have repeated cards with same face value. Else, push to temp_cards.
	5) Extract the suit of cards in temp. If not found in temp_suits, push to it.
	6) If the size of temp_suits is greater than 1 return false. A run must have the same suit.
	7) Calculate tha face values of the cards temp and push to face_values
	8) Get the difference between the minimum and maximum face values in face_values minus the number of cards whose face values fall between them
	9) If the difference is less than or equal to sum of wildcards and jokers + 1, return True, else return false.
Assistance Received: none
********************************************************************* */

bool Player::checkRun(vector<Card> current_hand_to_check) {
	if (current_hand_to_check.size() < 3) {
		return false;
	}
	int total_applicable_wildcards = 0;
	vector<string> temp = handWithoutWildcards(current_hand_to_check, total_applicable_wildcards);
	if (temp.size() <= 1) {
		return true;
	}
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

/* *********************************************************************
Function Name: facesMaxDiff
Purpose: To find the maximum difference between the minimum and max face values of the vector of integers passed minus the face_values that fall between the min and max. 
Parameters:
	face_values, a vector of integers containing the face values
	vec_size, size of the vector
Return Value: Difference of max element - min element - number of elements whose face value is between max and min
Local Variables:
	start, an integer to store index of the minimum element in the vector
	end, an integer to store index of max element in the vector
	max_diff, an integer to store (end-start)-(number of cards whose value is between end and start)
Assistance Received: none
********************************************************************* */

int Player::facesMaxDiff(vector<int> face_values, int vec_size) {
	int start = -5;
	int end = -5;
	int max_diff = face_values[1] - face_values[0];
	for (int i = 0; i < vec_size; i++) {
		for (int j = i + 1; j < vec_size; j++) {
			if (face_values[j] - face_values[i] > max_diff) {
				max_diff = face_values[j] - face_values[i];
				end = face_values[j];
				start = face_values[i];
			}
		}
	}

	for (int i = 0; i < vec_size; i++) {
		if (face_values[i] > start && face_values[i] < end) {
			max_diff--;
		}
	}

	return max_diff;
}

/* *********************************************************************
Function Name: checkIfJoker
Purpose: To check if the card passed as a string is joker
Parameters:
	current_card, a string representing a card object
Return Value: Boolean: True if card is joker, false otherwise.
Local Variables:
	number, an integer storing the 2nd character of string joker object
Assistance Received: none
********************************************************************* */

bool Player::checkIfJoker(string current_card) {
	
	if ((current_card.at(0) == 'J') && isdigit(current_card.at(1))) {
		int number = current_card.at(1) - '0';

		if (number > 0 && number < 4) {
			return true;
		}
	}

	return false;
}

/* *********************************************************************
Function Name: checkIfWildcard
Purpose: To check if the card passed as a string is wildcard
Parameters:
	current_card, a string representing a card object
Return Value: Boolean: True if card is wildcard, false otherwise.
Local Variables:
	number, an integer representing face value of the card
Assistance Received: none
********************************************************************* */

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

/* *********************************************************************
Function Name: goOut
Purpose: To check if the current player can go out and update the best book/run combination and sum of cards remaining after forming the combination
Parameters:
	None
Return Value: Boolean: True if the player can goOut, false otherwise.
Local Variables:
	total_cards, an integer containing the total number of cards in the current hand.
Algorithm:
	1) Call the checkJokercards and checkWildcards methods to update the count of number of jokers and wildcards in hand
	2) Computer the sum of all the cards in the hand before forming any books or runs and save that to hand_score
	3) Call the bestBookRunCombination function with current player's hand as the parameter which will set the value of hand_score as sum of remaining cards after best possible book/run combination
	4) If hand_score is 0, meaning all cards are part of a book or run, return True. Else return False.

Assistance Received: none
********************************************************************* */

bool Player::goOut() {
	checkJokercards();
	checkWildcards();
	int total_cards = current_player_hand.size();
	hand_score = calculateSumOfCards(current_player_hand);
	//best_combination.clear();
	child_returning_smallest_sum.clear();
	//TODO changed int score = bestBookRunCombination to simply calling bestBookRunCombination
	//int score = bestBookRunCombination(current_player_hand);
	bestBookRunCombination(current_player_hand);

	if (hand_score == 0) {
		return true;
	}

	return false;
}

/* *********************************************************************
Function Name: bestBookRunCombination
Purpose: To generate the best combination of books and runs in the hand passed as parameter and store the sum of cards remaining after best combination in hand_score
Parameters:
	current_hand, a vector of Card objects	
Return Value: Boolean: hand_score, an integer of the sum of cards remaining after forming best book/run combination
Local Variables:
	current_hand_str, a vector of string representation of the current hand.
	listof_booksandruns_currenthand, a vector of vector of cards containing list of all possible books and runs in the current hand
	score, an integer to computer and store the sum of cards
	temp, a vector of strings to store the cards from the player's hands
	hand_after_removal, vector of strings after removing a book or a run cards from the list
	face, suit, chars for storing face and suit of card
	s_face, s_suit corresponding strings to face and suit
	current_card, a card object representing face and suit of s_face and s_suit
Algorithm:
	1) Get a vector of vector of cards which represents all the possible book/runs that the current hand can form.
	2) If the size of the vector containing vector of cards that represent books and runs is zero, calculate the sum of the cards.
	3) If the sum is less than the sum of all cards in the hand, save the sum to hand_score and the current_hand_str for parameter that called the function and return hand_score.
	4) Otherwise, for every book/run combination found, remove the cards in the book/run from the hand and call the function self-recursively.
Assistance Received: The recursive algorithm was provided in the class by Prof. Kumar
********************************************************************* */

int Player::bestBookRunCombination(vector<Card> current_hand) {
	vector<string> current_hand_str = handToStr(current_hand);
	
	/* TO DO -> CHANGE THIS WITH LINE ABOVE
	for (vector<Card>::iterator it = current_hand.begin(); it < current_hand.end(); it++) {
		string card = it->cardToString();
		current_hand_str.push_back(card);
	}
	*/
	
	vector<vector<Card>> listof_booksandruns_currenthand = generatePossibleCombinations(current_hand_str);

	if (listof_booksandruns_currenthand.size() == 0) {
		int score = calculateSumOfCards(current_hand);
		
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
				child_returning_smallest_sum = temp;
			}
			hand_score = score;
		}

		return hand_score;
	}


	for (auto i = listof_booksandruns_currenthand.begin(); i < listof_booksandruns_currenthand.end(); i++) {
		vector<Card> hand_after_removal;
		vector<string> temp_hand_for_removal = current_hand_str;
		for (auto j = i->begin(); j < i->end(); j++) {
			temp_hand_for_removal.erase(remove(temp_hand_for_removal.begin(), temp_hand_for_removal.end(), j->cardToString()), temp_hand_for_removal.end());
		}

		vector<string>::iterator it;

		for (it = temp_hand_for_removal.begin(); it < temp_hand_for_removal.end(); it++) {
			char face = (*it)[0];
			char suit = (*it)[1];
			string s_face(1, face);
			string s_suit(1, suit);
			Card current_card = Card(s_face, s_suit);
			hand_after_removal.push_back(current_card);
		}

		bestBookRunCombination(hand_after_removal);
	}

}

/* *********************************************************************
Function Name: calculateSumOfCards
Purpose: To calculate the sum of cards passed as argument with the value that the cards represent in that round when calculating points.
Parameters:
	remaining_cards, a vector of card objects for which the sum is to be calculated
Return Value: score, an integer containing the sum of the cards.
Local Variables: 
	score, an integer to store the sum of cards.
	check_if_wildcard, check_if_joker, booleans to check if the current card is wildcard or joker. 
Assistance Received: None
********************************************************************* */

int Player::calculateSumOfCards(vector<Card> remaining_cards) {
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

	return score;
}

/* *********************************************************************
Function Name: generatePossibleCombinations
Purpose: To generate a list of combinations of cards in the current hand, pass it to a check book or run function, and return a vector containing vector of cards representing all possible books and runs.
Parameters:
	current_player_hand_str, a vector of strings containing the current player's hand.
Return Value: Vector of vector of cards where each vector represents a possible book/run combination.
Local Variables:
	possible_combinations, a vector of vectors of strings where each vector is a possible  combination.
	x_faces, a vector of strings containing cards whose faces are 'X'. Need it to put the cards in proper order after sorting.
	k_faces, a vector of strings containing cards whose faces are 'K'. Need it to put cards in proper order after sorting.
	wildcardsandjokers, a vector of strings to store the wildcards and jokers in the hand.
	current_card, a string to hold the current card
	first, an integer initialized to 50. Used to find the first occurence of 'J' cards except jokers or 'Q' cards if exists to find the right position for 'X' cards.
	max_numofcards_in_combination, an integer containing the number of cards in the hand.
	min_numofcards_in_combination, an integer required when generating combinations.
	numofcards_in_current_combination, an integer used for the for loop when generating combinations of cards for different sizes.
	copy_possible_combinations, a vector of vector of strings to store the possible_combinations before pushing wildcards and jokers to them.
Algorithm:
	1) Sort the hand.
	2) Check if the hand has wildcards, jokers, or cards with face values 'X' or 'K'. If so, remove them from the hand and save them on their own vectors.
	3) Sort the vectors containing cards with 'X' and 'K' if they are not empty.
	4) Find the position of first occurence, if exists, of a card 'J' or 'Q' in the remaining hand, the cards in X's vector should be inserted from this position.
	5) Insert vector containing K cards at the end.
	6) Declara max number of combination as the max size of the hand minus the number of wildcards and jokers. Declare minimum as 3 minus the number of wildcards and jokers.
	7) Loop while minimum is less than max number in combination, and for every index extract cards in the hand for the current size starting from minimum and ending at maximum.
	8) For every suit, check if cards in the current hand belong to that suit. If so, add those cards to a vector containing cards of that suit and sort it.
	9) Find combinations of different sizes within vectors containing cards of a suit as done in step 7, and if they're not already stored as a list of possible combinations, store it.
	10) Add wildcards and jokers to every combination extracted of all lengths.
	11) Pass the extracted vector of vector of strings containing all combinations to listBooksAndRuns function.
Assistance Received: None
********************************************************************* */

vector<vector<Card>> Player::generatePossibleCombinations(vector<string> current_player_hand_str) {
	vector<vector<string>> possible_combinations;
	sort(current_player_hand_str.begin(), current_player_hand_str.end());
	vector<string> x_faces;
	vector<string> k_faces;
	vector<string> wildcardsandjokers;
	vector<string>::iterator it;

	//Remove, wildcards, jokers, Xs and Ks

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

	//Sort vectors containing cards with faces Xs and Ks
	sort(x_faces.begin(), x_faces.end());
	sort(k_faces.begin(), k_faces.end());
	
	int first = 50;

	//Find first position of Js and Qs if exists, to find the right position to insert cards Xs

	for (auto i = current_player_hand_str.begin(); i < current_player_hand_str.end(); i++) {
		string current_card = *i;
			if (current_card.at(0) == 'J' || current_card.at(0) == 'Q') {
				auto finder = find(current_player_hand_str.begin(), current_player_hand_str.end(), *i);
				if (finder == current_player_hand_str.end()) {
					cout << "Some error " <<endl;
				}
				else {
					auto index = distance(current_player_hand_str.begin(), finder);
					if (index < first) {
						first = index;
					}

				}
			}
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
	
	//Add Ks to the end 

	for (auto i = k_faces.begin(); i < k_faces.end(); i++) {
		current_player_hand_str.push_back(*i);
	}


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

	while (numofcards_in_current_combination <= max_numofcards_in_combination) {
		start_index_current_combination = 0;

		while (start_index_current_combination <= (max_numofcards_in_combination - numofcards_in_current_combination)) {
			vector<string> current_combination;
			for (int i = start_index_current_combination; i < (numofcards_in_current_combination + start_index_current_combination); i++) {
				if (i < current_player_hand_str.size()) {
					current_combination.push_back(current_player_hand_str[i]);
				}
			}
			possible_combinations.push_back(current_combination);
			start_index_current_combination++;
		}
		numofcards_in_current_combination++;
	}

	vector<string> suits = { "S", "C", "D", "H", "T" };

	for (auto it = suits.begin(); it < suits.end(); it++) {
		string current_suit = *it;
		char current_char = current_suit.at(0);
		vector<string> current_suit_cards;

		for (auto i = current_player_hand_str.begin(); i < current_player_hand_str.end(); i++) {
			if ((*i)[1] == current_char) {
				current_suit_cards.push_back(*i);
			}
		}

		max_numofcards_in_combination = current_suit_cards.size();
		numofcards_in_current_combination = min_numofcards_in_combination;

		while (numofcards_in_current_combination <= max_numofcards_in_combination) {
			start_index_current_combination = 0;
			while (start_index_current_combination <= (max_numofcards_in_combination - numofcards_in_current_combination)) {
				vector<string> current_combination;

				for (int i = start_index_current_combination; i < (numofcards_in_current_combination + start_index_current_combination); i++) {
					if (i < current_suit_cards.size()) {
						current_combination.push_back(current_suit_cards[i]);
					}
				}

				if (!(find(possible_combinations.begin(), possible_combinations.end(), current_combination) != possible_combinations.end())) {
					possible_combinations.push_back(current_combination);
				}
				start_index_current_combination++;
			}
			numofcards_in_current_combination++;
		}

	}

	vector<vector<string>> copy_possible_combinations;
	copy_possible_combinations = possible_combinations;
	
	for (auto i = copy_possible_combinations.begin(); i < copy_possible_combinations.end(); i++) {
		vector<string> temp = *i;
		for (auto j = wildcardsandjokers.begin(); j < wildcardsandjokers.end(); j++) {
			temp.push_back(*j);
			possible_combinations.push_back(temp);
		}
	}
	return listBooksAndRuns(possible_combinations);
}

/* *********************************************************************
Function Name: listBooksAndRuns
Purpose: To find a list of books and runs within a vector of vector of strings passed as parameter and return it.
Parameters:
	possible_combinations, a vector of vectors of strings containing all possible combinations of cards in the current hand.
Return Value: a vector of vector of cards where each inner vector represents either a possible book or a run in the current hand.
Local Variables:
	checkbook, checkrun, booleans to check if the current hand belong to books or runs respectively.
	list_books_and_runs, a vector of vector of cards to store all the books and runs found.
	current_hand_combination, a vector of cards to store the current hand.
	face, suit, characters to extract the face and suit of the current hand respectively.
	s_face, s_suit, strings corresponding to face and suit characters.
Algorithm:
	1) Extract each vector and pass it to checkbook and checkrun function
	2) If either of them return true, append to list_books_and_runs
	3) Return list_books_and_runs
Assistance Received: none
********************************************************************* */

vector<vector<Card>> Player::listBooksAndRuns(vector<vector<string>> possible_combinations) {
	
	bool checkbook, checkrun;
	vector<vector<Card>> list_books_and_runs;
	
	for (int i = 0; i < list_books_and_runs.size(); i++) {
		list_books_and_runs[i].clear();
	}
	
	char face, suit;

	for (auto i = possible_combinations.begin(); i < possible_combinations.end(); i++) {
		vector<Card> current_hand_combination;
		for (auto j = i->begin(); j < i->end(); j++) {
			face = (*j)[0];
			suit = (*j)[1];
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
	
	return list_books_and_runs;
}


//Returns the current hand_score

int Player::getHandScore() const {
	return hand_score;
}

/* *********************************************************************
Function Name: getCurrentHand
Purpose: To get a space seperated string representation of the user's current hand.
Parameters:
	None
Return Value: a space seprated string representation of the user's current hand.
Local Variables:
	current_hand_space_sep, to store the cards as string and return 
Assistance Received: none
********************************************************************* */

string Player::getCurrentHand() {
	string current_hand_space_sep;
	for (auto const& onecard : current_player_hand_str) {
		current_hand_space_sep = current_hand_space_sep + onecard + " ";
	}
	return current_hand_space_sep;
}

/* *********************************************************************
Function Name: clearCurrentHand
Purpose: To clear the player's hand
Parameters:
	None
Return Value: None
Local Variables:
	None
Assistance Received: none
********************************************************************* */

void Player::clearCurrentHand() {
	total_cards_in_hand = 0;
	total_wildcards_num = 0;
	total_jokers_num = 0;
	current_player_hand.clear();
	current_player_hand_str.clear();
}

/* *********************************************************************
Function Name: printAvailableBooksandRuns
Purpose: To print available books and runs to the console if exists.
Parameters:
	None
Return Value: None
Local Variables:
	None
Assistance Received: none
********************************************************************* */

void Player::printAvailableBooksandRuns() {
	if (child_returning_smallest_sum.size() == 0) {
		cout << "The current player has no books or runs in hand " << endl;
	}
	else {
		cout << " The available books and runs are: " << endl;
		for (auto i = child_returning_smallest_sum.begin(); i < child_returning_smallest_sum.end(); i++) {
			cout << *i << "   ";
		}
	}
	cout << endl;
}

//Default destructor

Player::~Player()
{
}
