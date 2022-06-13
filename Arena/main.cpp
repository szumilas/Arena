#include "TurboSnakePlayerRandom.h"
#include "TurboSnakePlayerGreedy.h"

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
	int singleFrameDurationTime = 20; // [ms]

	//------------------------------------------------------------------
	// Remember to adjust console window to size gameWidth x gameHeight
	//------------------------------------------------------------------

	TurboSnakeGame game(Game::Strategy::TurnBased, singleFrameDurationTime, gameWidth, gameHeight);

	game.AddPlayer<TurboSnakePlayerGreedy>('A');
	game.AddPlayer<TurboSnakePlayerGreedy>('B');
	game.AddPlayer<TurboSnakePlayerGreedy>('C');
	game.AddPlayer<TurboSnakePlayerGreedy>('D');
	game.AddPlayer<TurboSnakePlayerGreedy>('E');

	game.Start();
}