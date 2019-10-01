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
	string getCurrentHand();
	virtual void pickCard();
	virtual void dropCard();
	void calculatePoints();
	void decreaseHandCardNum();
	int getWildcardsNum();
	void checkWildcards();
	int getJokersNum();
	void checkJokercards();
	bool goOut();
	void setCurrentRoundNum(int);
	int getCurrentRoundNum();
	
	bool checkBook(vector<Card> handToCheck);
	bool checkRun(vector<Card> handToCheck);
	
	bool checkIfJoker(string);
	bool checkIfWildcard(string);
	int getPlayerPoints();
	void setPlayerHand(vector<string>);

	vector<string> handToStr(vector<Card>);
	
	vector<string> handWithoutWildcards(vector<Card>, int &);
	int facesMaxDiff(vector<int>, int);

	void getCombination(vector<Card>, int, int);
	void combinationUtil(vector<Card>, vector<Card>, int, int, int, int);


	~Player();

protected:
	vector<Card> current_player_hand;
	vector<string> current_player_hand_str;
	int total_cards_in_hand;
	int total_wildcards_num;
	int total_jokers_num;
	int current_round_num;
	int current_round_score;
};

