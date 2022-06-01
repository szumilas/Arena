#include "TurboSnakePlayerRandom.h"

TurboSnakeOutput TurboSnakePlayerRandom::GetMove()
{
	return rand() % 4 + 1;
}

