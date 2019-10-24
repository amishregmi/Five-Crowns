/*
************************************************************
* Name:  Amish Regmi                                       *
* Project : Project 1, Five Crowns (C++)                   *
* Class : CMPS 366 01                                      *
* Date : 10/22/2019                                        *
************************************************************
*/

#pragma once
#include "Player.h"
#include "Card.h"

class Human : public Player 
{
public:
	//Default Constructor
	Human();

	//Function to get help from computer on which card to pick
	void pickCardHelp();
	
	//Function to pick card and add to the hand
	void pickCard();

	//Function to get help on which card to drop
	void dropCardHelp();

	//Function to drop a card
	void dropCard();

	//Function to get help on assembling books and runs and check if you can go out
	void booksRunsAndGoOut();

	//Default destructor
	~Human();

};

