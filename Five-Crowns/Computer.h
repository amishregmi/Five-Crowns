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