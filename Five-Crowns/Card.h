#pragma once
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

	void setFace(string);

	void setSuit(string);

	void printCard();

	string cardToString();

	~Card();
};

