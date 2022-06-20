#pragma once

#include "Player.h"
#include "TurboFrogGame.h"

class TurboFrogPlayer : public Player
{
	friend class TurboFrogGame;

public:
	TurboFrogPlayer(std::string teamName) : teamName(teamName) {}

protected:

	int nextMove = 0;
	TurboFrogGame* game = nullptr;

	int x{};
	int y{};

private:
	inline void SetPosition(int newx, int newy) { x = newx; y = newy; }
	inline void AddPoints(int point) { points += point; }
	void Initialize(TurboFrogGame*, char);
	void ResetNextMove() { nextMove = 0;}

	int points = 0;

	char sign;
	std::string teamName;
};