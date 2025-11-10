#include "FootballGame.h"
#include "FootballPlayer_Team1.h"
#include "FootballPlayer_Team2.h"
#include "FootballPlayer_Team3.h"
#include "FootballPlayer_Team4.h"
#include "FootballPlayer_Team_TEMPLATE.h"

#include <memory>

#include <stdio.h>
#include <string>
#include <windows.h>
#include <chrono>
#include <iostream>

int main()
{
	int gameWidth = 111;               // [characters]
	int gameHeight = 70;               // [characters]

	//------------------------------------------------------------------
	// Remember to adjust console window to size gameWidth x gameHeight
	//------------------------------------------------------------------

	FootballGame game(11, 3, Game::Strategy::TurnBased, gameWidth, gameHeight);

	game.AddPlayer<FootballPlayer_Team2>("Team 2");
	game.AddPlayer<FootballPlayer_Team3>("Team 3");
	

	game.Start();
}