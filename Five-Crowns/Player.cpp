#include "Player.h"



Player::Player()
{
	total_cards_in_hand = 0;
}


void Player::addCardToHand(Card card){
	total_cards_in_hand++;
	current_player_hand.push_back(card);
	string card_str = card.cardToString();
	current_player_hand_str.push_back(card_str);
	//checkWildcards(current_round_num);

}

void Player::checkWildcards() {
	if (current_round_num != 0){
		cout << endl;
		cout << "Current roundNumber inside checkWildCards is: " << current_round_num << endl;
		total_wildcards_num = 0;

		for (vector<string>::iterator i = current_player_hand_str.begin(); i != current_player_hand_str.end(); ++i) {
			string current_card = *i;
			//cout << "Current card is: " <<current_card << endl;
			 
			//Need to check wildcards for rounds 10, 11, 12, 13 for faces

			if (isdigit(current_card.at(0))) {
				int number = current_card.at(0) - '0';
				if (number == (current_round_num+2)) {
				//	cout << "Inside firstdigit is roundnumber " << endl;
					total_wildcards_num++;
				}
			}
			//((stoi(current_card) == 1 || stoi(current_card) == 2 || stoi(current_card) == 3))
			if ((current_card.at(0) == 'J') && isdigit(current_card.at(1) )){

				int number = current_card.at(1) - '0';

				if (number > 0 && number < 4) {
					total_wildcards_num++;
				}				
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


Player::~Player()
{
}
