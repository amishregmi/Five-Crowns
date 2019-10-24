/*
************************************************************
* Name:  Amish Regmi                                       *
* Project : Project 1, Five Crowns (C++)                   *
* Class : CMPS 366 01                                      *
* Date : 10/22/2019                                        *
************************************************************
*/

#pragma once
#include "Card.h"
#include "Deck.h"
#include<vector>
#include <typeinfo>
#include <ctype.h>
#include <algorithm>

class Player
{
public:
	//Default constructor for player class
	Player();

	//Add a card to the hand
	void addCardToHand(Card);

	//function to set the current player hand
	void setPlayerHand(vector<string>);

	//function to check the total number of jokers in the hand
	void checkJokercards();

	//function to check the total number of wildcards in the hand and save the number
	void checkWildcards();

	//set the current round number
	void setCurrentRoundNum(int);

	//function to print the current hand to the console
	void printCurrentHand();

	//virtual function pickCardHelp
	virtual void pickCardHelp();

	//virtual function pickCard
	virtual void pickCard();

	//virtual function dropCard
	virtual void dropCard();

	//function to check if a string representation of a card is a joker
	bool checkIfJoker(string);

	//function to check if a string representation of a card is a wildcard
	bool checkIfWildcard(string);

	//function to check if the current player can go out
	bool goOut();

	//get the current hand score
	int getHandScore() const;

	//function that returns the string representation of the current hand
	string getCurrentHand();

	//clear the current player's hand
	void clearCurrentHand();

	//function to print available books and runs to console
	void printAvailableBooksandRuns();

	//default destructor
	~Player();

protected:
	vector<Card> current_player_hand;

	vector<string> current_player_hand_str;

	int total_cards_in_hand;

	vector<string> child_returning_smallest_sum;

private:

	//To get a vector of string representation of any hand passed as argument
	vector<string> handToStr(vector<Card>);

	//Get a vector of strings representation of hand passed in as arguments without wildcards and jokers
	vector<string> handWithoutWildcards(vector<Card>, int &);

	//To check if hand passed is a book
	bool checkBook(vector<Card> handToCheck);

	//To check if the hand passed is a run
	bool checkRun(vector<Card> handToCheck);

	//Find max difference of minimum and max face values of the vector of integers passed as argument minus the face_values that fall in between those two faces in the hand.
	int facesMaxDiff(vector<int>, int);

	//Generate best combination of books and runs in the hand passed as argument and store sum of cards not in the combination 
	int bestBookRunCombination(vector<Card>);

	//Calculate sum of cards passed as arguments with the value that the cards represent in that round when calling calculate points function.
	int calculateSumOfCards(vector<Card>);

	//Generate a list of possible combinations of the cards from the current player's hand
	vector<vector<Card>> generatePossibleCombinations(vector<string>);

	//To return a list of books and runs from the vector of vector of strings passed as argument
	vector<vector<Card>> listBooksAndRuns(vector<vector<string>> possible_combinations);

	int hand_score;
	int total_wildcards_num;
	int total_jokers_num;
	int current_round_num;
	vector<vector<string>> recursive_bookrun_hands;

};

