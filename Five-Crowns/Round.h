#pragma once
#include <iostream>
#include "Player.h"
#include "Human.h"
#include "Computer.h"
#include "Deck.h"
#include <time.h>
#include <fstream>
#include <sstream>

using namespace std;

const string SAVED_GAME = "./saved_game.txt";

class Round
{
private:
	//two players
	Player *playersList[2];
	string player_names[2];
	int next_player_index;
	Human human_player;
	Computer computer_player;
	Deck deck;
	
	int total_players_num;
	bool verify_go_out_first;
	bool verify_go_out_second;
	int roundNumber;

public:
//	static int roundNumber;
	static string next_player;
	Round(int roundNumber);
	void roundDetails();
	void printRoundDetails();
	void dealForRound();
	void startRound();
	string coinToss();
	void printPlayersDetails();
	void menuOptions();
	void saveGame();
	~Round();
};

