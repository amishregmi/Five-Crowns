#pragma once
#include "Card.h"
#include<vector>
#include<algorithm>
#include<random>
#include<chrono>

class Deck
{
public:
	//Default constructor
	Deck();
	
	//print the current draw Pile
	static void printDrawPile();

	//print the current Discard pile
	static void printDiscardPile();

	//Deal cards to the human and computer for current round
	static vector<Card> dealCards(int);
	
	//Prints the top discard pile card
	static void showTopDiscardCard();

	//Returns the top discard pile card and removes from discard pile
	static Card takeTopDiscardCard();

	//Prints the Top Draw Card
	static void showTopDrawCard();

	//Returns the Top Draw Card and removes from draw pile.
	static Card takeTopDrawCard();

	//Returns one string containing space seprated string values of draw pile. used to print during the game
	const static string getCurrentDrawPile();

	//Returns one string containing space seprated string values of discard pile. used to print during the game
	const static string getCurrentDiscardPile();

	//returns the top discard pile card without removing it from Deck
	static Card accessTopDiscardPileCard();

	//returns the top draw pile card without removing it from Hand
	static Card accessTopDrawPileCard();

	//Set the Draw pile
	static void setDrawPile(vector<string>);

	//Set the discard Pile
	static void setDiscardPile(vector<string>);

	//Add card to the discard pile
	static void pushToDiscardPile(Card card);

	//Resets the Deck for every round
	static void resetDeck();

	//Default destructor
	~Deck();

	//TODO below was public

private:
	static vector<Card> drawPile;
	static vector<Card> discardPile;
};

