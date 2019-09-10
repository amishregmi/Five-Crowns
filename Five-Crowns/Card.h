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
	Card(string face="N", string suit="N");
	
	string getFace();

	string getSuit();

	void printCard();

	~Card();
};

