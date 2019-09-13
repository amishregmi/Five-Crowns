#pragma once
#include "Card.h"
#include<vector>
#include<algorithm>
#include<random>
#include<chrono>

class Deck
{
public:
	Deck();
	
	//void shuffleDrawPile();

	void printDrawPile();

	void printDiscardPile();

	vector<Card> dealCards(int);

	~Deck();

private:
	vector<Card> drawPile;
	vector<Card> discardPile;

};

