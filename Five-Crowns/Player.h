#pragma once
#include "Card.h"
#include "Deck.h"
#include<vector>
class Player
{
public:
	Player();
	void addCardToHand(Card);
	void printCurrentHand();
	virtual void pickCard();
	virtual void dropCard();
	void decreaseHandCardNum();
	//void goOut();
	~Player();
protected:
	vector<Card> current_player_hand;
	int total_cards_in_hand;
};

