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
	int next_player_index;
	Human human_player;
	Computer computer_player;
	Deck deck;
	string next_player;
	int total_players_num;
	

public:
	Round(int roundNumber);
	void roundDetails();
	void printRoundDetails();
	void startRound();
	~Round();
};

