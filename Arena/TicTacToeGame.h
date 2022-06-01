#pragma once

#include "Game.h"

using TicTacToeOutput = std::pair<unsigned short, unsigned short>;

class TicTacToeGame : public Game
{
public:
	template<typename ...Args>
	TicTacToeGame(const Args&... args) : Game(args...) {}

	inline auto GetBoard() const { return &board; }
	virtual void Print();
	void MakeMove(const TicTacToeOutput&, char);
	Game::State GetState() final;

private:
	virtual void Initialize();


private:

	char board[3][3] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};

};