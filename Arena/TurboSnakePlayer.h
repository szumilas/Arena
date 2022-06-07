#pragma once

#include "Player.h"
#include "TurboSnakeGame.h"

class TurboSnakePlayer : public Player
{
	friend class TurboSnakeGame;

public:
	TurboSnakePlayer(char sign) : sign(sign) {};

protected:

	int nextMove = 0;

private:
	inline void SetPosition(int newx, int newy) { x = newx; y = newy; }
	inline void AddPoints(int point) { points += point; }
	void Initialize(TurboSnakeGame*);
	TurboSnakeGame* game = nullptr;

	int points = 0;
	int x{};
	int y{};

	char sign;
};