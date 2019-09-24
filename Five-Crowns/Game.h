#pragma once
#include "Round.h"


class Game
{
public:
	Game();
	void callRound(int);
	void extractDetailsFromFile(string);
	vector<string> extract_card_str(string);
	~Game();
private:
	int human_player_points;
	int computer_player_points;
	int round_number;
	Player human;
	Player computer;
	string next_player;
};

