#pragma once

#include "Player.h"
#include "TurboBeeGame.h"

class TurboBeePlayer : public Player
{
	friend class TurboBeeGame;

public:
	TurboBeePlayer(std::string teamName) : teamName(teamName) {}

	struct Position
	{
		int x;
		int y;
	};

	char elementPlayerCovers = '#';

	inline std::list<Flower>& GetFlowers() { return game->GetFlowers(); }
	std::list<Position> GetOponentsPositions();
	char GetMapElement(int x, int y) { return game->GetMapElement(x, y); }
	inline int GetMyX() { return x; }
	inline int GetMyY() { return y; }
	inline int GetBagValue() { return bag; }
	inline int GetMapWidth() { return game->GetMapWidth(); }
	inline int GetMapHeight() { return game->GetMapHeight(); }

protected:

	NEXTMOVE nextMove = NEXTMOVE::IDLE;

private:
	inline void SetPosition(int newx, int newy) { x = newx; y = newy; }
	inline void AddPoints(int point) { points += point; }
	inline void AddPollenToBag() { bag++; }
	inline void ResetBag() { bag =0; }
	void Initialize(TurboBeeGame*, char);
	void ResetNextMove() { nextMove = NEXTMOVE::IDLE; }

	int points = 0;
	int bag = 0;

	int x{};
	int y{};

	char sign;
	std::string teamName;

	TurboBeeGame* game = nullptr;
};