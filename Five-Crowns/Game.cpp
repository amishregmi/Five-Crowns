#include "Game.h"



Game::Game()
{
	human_player_points = 0;
	computer_player_points = 0;
	round_number = 1;

}

void Game::callRound(int round_number = 0) {
	//Main game loop
	//while (round_number <= 13) {
		Round round(round_number);
		round.printRoundDetails();
		//round_number++;
	//}
}


Game::~Game()
{
}
