#pragma once

#include "TicTacToePlayer.h"

class TicTacToePlayerRandom : public TicTacToePlayer
{
public:
	template<typename ...Args>
	TicTacToePlayerRandom(const Args&... args) : TicTacToePlayer(args...) {}

private:
	TicTacToeOutput GetMove();
};