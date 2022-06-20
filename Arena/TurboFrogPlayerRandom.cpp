#include "TurboFrogPlayerRandom.h"

void TurboFrogPlayerRandom::CalculateNextMove()
{
	nextMove = rand() % 4 + 1;
}
