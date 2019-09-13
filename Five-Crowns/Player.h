#pragma once
#include "Card.h"
#include<vector>
class Player
{
public:
	Player();
	void addCardToHand(Card);
	void printCurrentHand(string);
	virtual void pickCard();
	virtual void dropCard();
	//void goOut();
	~Player();
private:
	vector<Card> current_player_hand;

};

