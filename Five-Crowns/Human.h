#pragma once
#include "Player.h"
#include "Card.h"

class Human : public Player 
{
public:
	Human();
	//void addCardToHand(Card);
	//void printCurrentHard();
	void dropCard();
	void pickCard();
	//void calculatePoints();
	void pickCardHelp();
	void dropCardHelp();
	void booksRunsAndGoOut();

	~Human();

//private:
	//vector<Card> human_hand;
};

