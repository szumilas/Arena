#include "TurboFrogPlayerRandom.h"
#include "TurboFrogPlayerGreedy.h"
#include "TurboFrogPlayerShy.h"
#include "TurboFrogPlayerBigFish.h"
#include "TurboFrogPlayerBigFishSmart.h"

#include <memory>

#include <stdio.h>
#include <string>
#include <windows.h>
#include <chrono>
#include <iostream>

int main()
{
	int gameWidth = 88;                // [characters]
	int gameHeight = 50;               // [characters]

	//------------------------------------------------------------------
	// Remember to adjust console window to size gameWidth x gameHeight
	//------------------------------------------------------------------

	TurboFrogGame game(Game::Strategy::TurnBased, gameWidth, gameHeight);

	game.AddPlayer<TurboFrogPlayerGreedy>("Greedy");
	game.AddPlayer<TurboFrogPlayerShy>("Shy");
	game.AddPlayer<TurboFrogPlayerBigFish>("BigFish");
	game.AddPlayer<TurboFrogPlayerBigFishSmart>("BigFishSmart");

	game.Start();
}