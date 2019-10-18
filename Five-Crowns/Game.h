#pragma once
#include "Round.h"
#include "Deck.h"


class Game
{
public:
	Game();
	void callRound();
	void extractDetailsFromFile(string);
	vector<string> extract_card_str(string);
	string coinToss();
	static int getHumanTotalPoints();
	static int getComputerTotalPoints();
	~Game();
private:
	static int human_player_points;
	static int computer_player_points;
	int round_number;
	Human human;
	Computer computer;
	string next_player;
	bool read_from_file;
	Deck deck;
};

