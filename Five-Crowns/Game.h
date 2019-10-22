#pragma once
#include "Round.h"
#include "Deck.h"


class Game
{
public:
	//Constructor
	Game();

	//Function to set up and start a round
	void callRound();

	//Function to extract the required serialization details
	void extractDetailsFromFile(string);

	//Function to extract individual cards from a string containing space separated string representation of cards
	vector<string> extract_card_str(string);

	//Function to toss the coin for first round and set the first player
	string coinToss();

	//Function to get human player's points for a round
	const static int getHumanTotalPoints();

	//Function to get the compter player's points for a round
	const static int getComputerTotalPoints();

	//Default destructor
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

