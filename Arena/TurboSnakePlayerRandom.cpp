#include "TurboSnakePlayerRandom.h"

void TurboSnakePlayerRandom::CalculateNextMove()
{
	nextMove = rand() % 4 + 1;
}
