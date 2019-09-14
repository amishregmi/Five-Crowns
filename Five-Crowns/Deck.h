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

	static void printDrawPile();

	static void printDiscardPile();

	vector<Card> dealCards(int);

	static void showTopDiscardCard();

	static Card takeTopDiscardCard();

	static void showTopDrawCard();

	static Card takeTopDrawCard();

	~Deck();

public:
	static vector<Card> drawPile;
	static vector<Card> discardPile;
};

