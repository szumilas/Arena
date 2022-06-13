#pragma once

#include "Player.h"
#include "TurboSnakeGame.h"

class TurboSnakePlayer : public Player
{
	friend class TurboSnakeGame;

public:
	TurboSnakePlayer(std::string teamName) : teamName(teamName) {}

protected:

	int nextMove = 0;
	TurboSnakeGame* game = nullptr;

	int x{};
	int y{};

private:
	inline void SetPosition(int newx, int newy) { x = newx; y = newy; }
	inline void AddPoints(int point) { points += point; }
	void Initialize(TurboSnakeGame*, char);
	void ResetNextMove() { nextMove = 0;}

	int points = 0;

	char sign;
	std::string teamName;
};