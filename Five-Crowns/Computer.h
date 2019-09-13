#pragma once
#include "Player.h"
#include "Card.h"

class Computer: public Player
{
public:
	Computer();
	void dropCard();
	void pickCard();
	~Computer();
//private:
	//vector<Card> computer_hand;
};

