#pragma once
#include<iostream>
#include<string>

using namespace std;

class Card
{

public:
	//Card class constructor
	Card(string face="N", string suit="N");	

	//Face getter function
	const string getFace();

	//Suit getter function
	const string getSuit();

	//sets face of the current card
	void setFace(string);

	//sets suit of the current card
	void setSuit(string);

	//prints the current card
	void printCard();

	//returns string representation of the current card
	string cardToString();

	//Default Destructor
	~Card();

private:
	string face;
	string suit;
};

