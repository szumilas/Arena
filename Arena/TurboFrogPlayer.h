#pragma once

#include "Player.h"
#include "TurboFrogGame.h"

class TurboFrogPlayer : public Player
{
	friend class TurboFrogGame;

public:
	TurboFrogPlayer(std::string teamName) : teamName(teamName) {}

	struct Position
	{
		int x;
		int y;
	};

	inline std::list<BonusPoint>& GetBonusPoints() { return game->GetBonusPoints(); }
	std::list<Position> GetOponentsPositions();
	char GetMapElement(int x, int y) { return game->GetMapElement(x, y); }
	inline int GetMyX() { return x; }
	inline int GetMyY() { return y; }
	inline int GetMapWidth() { return game->GetMapWidth(); }
	inline int GetMapHeight() { return game->GetMapHeight(); }

protected:

	int nextMove = 0;

private:
	inline void SetPosition(int newx, int newy) { x = newx; y = newy; }
	inline void AddPoints(int point) { points += point; }
	void Initialize(TurboFrogGame*, char);
	void ResetNextMove() { nextMove = 0;}

	int points = 0;

	int x{};
	int y{};

	char sign;
	std::string teamName;

	TurboFrogGame* game = nullptr;
};