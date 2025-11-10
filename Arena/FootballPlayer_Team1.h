#pragma once

#include "FootballPlayer.h"

class FootballPlayer_Team1 : public FootballPlayer
{
public:
	template<typename ...Args>
	FootballPlayer_Team1(const Args&... args) : FootballPlayer(args...) { }

private:
	void CalculateNextMove();

	std::map<int, Coordinates> GetDefaultPositions();
};