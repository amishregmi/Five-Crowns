#pragma once
#include<deque>
#include "Card.h"
#include<algorithm>

class Deck
{
public:
	Deck();
	
	//void shuffleDrawPile();

	void printDrawPile();


	~Deck();

private:
	deque<Card> drawPile;
	deque<Card> discardPile;

};

