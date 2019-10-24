/*
************************************************************
* Name:  Amish Regmi                                       *
* Project : Project 1, Five Crowns (C++)                   *
* Class : CMPS 366 01                                      *
* Date : 10/22/2019                                        *
************************************************************
*/

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
	string getFace() const;

	//Suit getter function
	string getSuit() const;

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

