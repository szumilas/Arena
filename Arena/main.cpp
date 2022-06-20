#include "TurboFrogPlayerRandom.h"
#include "TurboFrogPlayerGreedy.h"

#include <memory>

#include <stdio.h>
#include <string>
#include <windows.h>
#include <chrono>
#include <iostream>

int main()
{
	int gameWidth = 90;               // [characters]
	int gameHeight = 50;              // [characters]

	//------------------------------------------------------------------
	// Remember to adjust console window to size gameWidth x gameHeight
	//------------------------------------------------------------------

	TurboFrogGame game(Game::Strategy::TurnBased, gameWidth, gameHeight);

	game.AddPlayer<TurboFrogPlayerGreedy>("Team name 1abcdefghijkl");
	game.AddPlayer<TurboFrogPlayerGreedy>("Team name 2abcdefghijkl");
	game.AddPlayer<TurboFrogPlayerRandom>("Team name 3abcdefghijkl");

	game.Start();
}