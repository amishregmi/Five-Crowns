/*
************************************************************
* Name:  Amish Regmi                                       *
* Project : Project 1, Five Crowns (C++)                   *
* Class : CMPS 366 01                                      *
* Date : 10/22/2019                                        *
************************************************************
*/

#pragma once
#include <iostream>
#include "Player.h"
#include "Human.h"
#include "Computer.h"
#include "Deck.h"
#include <time.h>
#include <fstream>
#include <sstream>
#include "Game.h"

using namespace std;

const string SAVED_GAME = "./saved_game.txt";

class Round
{
public:
	//Constructor for round class
	Round(int roundNumber, Human*, Computer*, string, bool);

	//Function to set up a round
	void roundDetails();

	//Function to print the details of the current round
	void printRoundDetails();

	//Function to deal rounds for the current round
	void dealForRound();

	//Function for the two players to play in the round
	void startRound();
	
	//Function to display menu options and get user input
	void menuOptions();

	//Function to save the current state of game to a text file
	void saveGame();

	//Function to return the current score of human player
	int getHumanScore();

	//Function to return current score of computer player
	int getComputerScore();

	//Function to return the string of the next player
	string getNextPlayer();
	
	//Default destructor
	~Round();

private:

	Player * playersList[2];
	string player_names[2];
	int next_player_index;
	Human human_player;
	Computer computer_player;
	int total_players_num;
	bool verify_go_out_first;
	bool verify_go_out_second;
	int roundNumber;
	bool readfromfile;

};

