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
	int gameHeight = 40;              // [characters]
	int singleFrameDurationTime = 50; // [ms]

	//------------------------------------------------------------------
	// Remember to adjust console window to size gameWidth x gameHeight
	//------------------------------------------------------------------

	TurboFrogGame game(Game::Strategy::TurnBased, singleFrameDurationTime, gameWidth, gameHeight);

	game.AddPlayer<TurboFrogPlayerGreedy>("Team name 1");
	game.AddPlayer<TurboFrogPlayerGreedy>("Team name 2");
	game.AddPlayer<TurboFrogPlayerGreedy>("Team name 3");

	game.Start();
}