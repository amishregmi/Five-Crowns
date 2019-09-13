#pragma once
#include <iostream>
#include "Player.h"
#include "Human.h"
#include "Computer.h"
#include "Deck.h"

using namespace std;

class Round
{
private:
	int roundNumber;
	//two players
	Player *playersList[2];
	int playerIndex;
	Human human_player;
	Computer computer_player;
	Deck deck;
	

public:
	Round(int roundNumber);
	void printRoundDetails();
	void startRound();
	~Round();
};

