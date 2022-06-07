#include "TurboSnakePlayerRandom.h"

#include <memory>

#include <stdio.h>
#include <string>
#include <windows.h>
#include <chrono>
#include <iostream>

int main()
{
	int gameWidth = 120;              // [characters]
	int gameHeight = 40;              // [characters]
	int singleFrameDurationTime = 50; // [ms]

	//------------------------------------------------------------------
	// Remember to adjust console window to size gameWidth x gameHeight
	//------------------------------------------------------------------

	TurboSnakeGame game(Game::Strategy::RealTime, singleFrameDurationTime, gameWidth, gameHeight);

	game.AddPlayer<TurboSnakePlayerRandom>('A');
	game.AddPlayer<TurboSnakePlayerRandom>('B');
	game.AddPlayer<TurboSnakePlayerRandom>('C');
	game.AddPlayer<TurboSnakePlayerRandom>('D');
	game.AddPlayer<TurboSnakePlayerRandom>('E');

	game.Start();
}