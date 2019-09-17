#pragma once
#include "Card.h"
#include "Deck.h"
#include<vector>
#include <typeinfo>
#include <ctype.h>
#include <algorithm>

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
	int getJokersNum();
	void checkJokercards();
	//void goOut();
	void setCurrentRoundNum(int);
	int getCurrentRoundNum();
	bool checkBook();
	bool checkRun();
	bool checkIfJoker(string);
	bool checkIfWildcard(string);
	~Player();
protected:
	vector<Card> current_player_hand;
	vector<string> current_player_hand_str;
	int total_cards_in_hand;
	int total_wildcards_num;
	int total_jokers_num;
	int current_round_num;
};

