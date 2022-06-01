#include "TicTacToePlayer.h"

void TicTacToePlayer::Move()
{
	game->MakeMove(GetMove(), sign);
}

void TicTacToePlayer::Initialize(TicTacToeGame* ticTacToe)
{
	game = ticTacToe;
}

TicTacToeOutput TicTacToePlayer::GetMove()
{

	return {0, 0};
}