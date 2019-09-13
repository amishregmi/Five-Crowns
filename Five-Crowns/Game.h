#pragma once
#include "Round.h"


class Game
{
public:
	Game();
	void callRound(int);
	~Game();
private:
	int human_player_points;
	int computer_player_points;
	int round_number;
};

