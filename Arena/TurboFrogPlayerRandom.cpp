#include "TurboFrogPlayerRandom.h"

void TurboFrogPlayerRandom::CalculateNextMove()
{
	//--------------------------------------------
	// Algorithm:
	// Goes randomly
	//--------------------------------------------

	nextMove = rand() % 4 + 1;
}
