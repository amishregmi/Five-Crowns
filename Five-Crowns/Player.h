#pragma once
#include "Card.h"
#include "Deck.h"
#include<vector>
#include <typeinfo>
#include <ctype.h>

class Player
{
public:
	Player();
	void addCardToHand(Card);
	void printCurrentHand();
	virtual void pickCard();
	virtual void dropCard();
	void decreaseHandCardNum();
	int getWildcardsNum();
	void checkWildcards();
	//void goOut();
	void setCurrentRoundNum(int);
	int getCurrentRoundNum();
	~Player();
protected:
	vector<Card> current_player_hand;
	vector<string> current_player_hand_str;
	int total_cards_in_hand;
	int total_wildcards_num;
	int current_round_num;
};

