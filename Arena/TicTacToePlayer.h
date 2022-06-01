#pragma once

#include "Player.h"
#include "TicTacToeGame.h"

class TicTacToePlayer : public Player
{
	friend class TicTacToeGame;

public:
	TicTacToePlayer(char sign) : sign(sign) {};

	inline auto GetBoard() const { return game->GetBoard(); }
	virtual TicTacToeOutput GetMove();

	const char sign = ' ';

private:
	virtual void Move();
	void Initialize(TicTacToeGame*);
	TicTacToeGame* game = nullptr;
};