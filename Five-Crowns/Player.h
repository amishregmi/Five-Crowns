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
	
	virtual void pickCardHelp();

	vector<vector<Card>> generatePossibleCombinations(vector<string>);
	
	void decreaseHandCardNum();
	
	int getWildcardsNum();
	
	void checkWildcards();
	
	int getJokersNum();
	
	void checkJokercards();
	
	bool goOut();
	
	void setCurrentRoundNum(int);
	
	const int getCurrentRoundNum();
	
	bool checkBook(vector<Card> handToCheck);
	
	bool checkRun(vector<Card> handToCheck);
	
	bool checkIfJoker(string);
	
	bool checkIfWildcard(string);
	
	
	int calculateSumOfCards(vector<Card>);

	int bestBookRunCombination(vector<Card>);

	void setPlayerHand(vector<string>);

	vector<vector<Card>> listBooksAndRuns(vector<vector<string>> possible_combinations);

	vector<string> handToStr(vector<Card>);
	
	vector<string> handWithoutWildcards(vector<Card>, int &);
	
	int facesMaxDiff(vector<int>, int);

	const int getHandScore();

	void clearCurrentHand();

	void printAvailableBooksandRuns();

	~Player();

protected:
	vector<Card> current_player_hand;
	
	vector<string> current_player_hand_str;
	
	int total_cards_in_hand;
	
	int total_wildcards_num;
	
	int total_jokers_num;
	
	int current_round_num;
	
	int current_round_score;

	//Used to keep track of combination of assembled cards with lowest score
	int hand_score; 

	//use to keep track of the best arrangement of cards for least points.
	vector<vector<string>> recursive_bookrun_hands;
	vector<vector<string>> best_combination;

	//Amruth algo TODO remove name
	vector<string> child_returning_smallest_sum;
	

};

