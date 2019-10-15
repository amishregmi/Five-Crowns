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

	static vector<Card> dealCards(int);

	static void showTopDiscardCard();

	static Card takeTopDiscardCard();

	static void showTopDrawCard();

	static Card takeTopDrawCard();

	static string getCurrentDrawPile();

	static string getCurrentDiscardPile();

	static Card accessTopDiscardPileCard();

	static Card accessTopDrawPileCard();

	static void setDrawPile(vector<string>);

	static void resetDeck();

	static void setDiscardPile(vector<string>);

	~Deck();

public:
	static vector<Card> drawPile;
	static vector<Card> discardPile;
};

