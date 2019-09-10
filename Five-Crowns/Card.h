#pragma once
#include "Round.h"
#include<iostream>
#include<string>

using namespace std;

class Card
{
private:
	string face;
	string suit;

public:
	Card();
	
	string getFace();

	string getSuit();

	void setFace(string face);

	void setSuit(string suit);

	void printCard();

	~Card();
};

