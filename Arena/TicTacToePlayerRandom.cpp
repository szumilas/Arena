#include "TicTacToePlayerRandom.h"

TicTacToeOutput TicTacToePlayerRandom::GetMove()
{
	return { rand() % 3, rand() % 3 };
}

