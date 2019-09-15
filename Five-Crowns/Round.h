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
	//two players
	Player *playersList[2];
	int next_player_index;
	Human human_player;
	Computer computer_player;
	Deck deck;
	string next_player;
	int total_players_num;
	bool verify_go_out;
	int roundNumber;

public:
//	static int roundNumber;
	Round(int roundNumber);
	static int getRoundNumber();
	void roundDetails();
	void printRoundDetails();
	void dealForRound();
	void startRound();
	void printPlayersDetails();
	~Round();
};

