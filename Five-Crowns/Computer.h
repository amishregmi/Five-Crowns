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

class Computer: public Player
{
public:
	//Default constructor
	Computer();

	//Function that overrides pickCard() in Player
	void pickCard();

	//Function that overrides dropCard() in Player
	void dropCard();
	
	//Default destructor
	~Computer();
};