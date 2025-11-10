#pragma once

#include "FootballPlayer.h"

class FootballPlayer_Team2 : public FootballPlayer
{
public:
	template<typename ...Args>
	FootballPlayer_Team2(const Args&... args) : FootballPlayer(args...) { }

private:
	void CalculateNextMove();

	void SetGoalkeeperMove();
	void SetDefenceMove();
	void SetMidfieldMove();
	void SetAtackMove();

	void FindClosestFootballerToBall();
	int FindClosestFootballerToFootballer(int id, double minDist = 0, bool excludeGoalkeeper = true, bool preferAtack = true);


	int closestToBall{};

};