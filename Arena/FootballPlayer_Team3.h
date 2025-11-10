#pragma once

#include "FootballPlayer.h"

class FootballPlayer_Team3 : public FootballPlayer
{
public:
	template<typename ...Args>
	FootballPlayer_Team3(const Args&... args) : FootballPlayer(args...) { }

private:
	void CalculateNextMove();
};