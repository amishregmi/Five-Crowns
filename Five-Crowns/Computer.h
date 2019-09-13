#pragma once
#include "Player.h"
#include "Card.h"

class Computer: public Player
{
public:
	Computer();
	void addCardToHand(Card);
	void printCurrentHard();
	~Computer();
private:
	vector<Card> computer_hand;
};

