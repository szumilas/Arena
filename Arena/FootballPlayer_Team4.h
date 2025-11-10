#pragma once

#include "FootballPlayer.h"

class FootballPlayer_Team4 : public FootballPlayer
{
public:
	template<typename ...Args>
	FootballPlayer_Team4(const Args&... args) : FootballPlayer(args...) { }

private:
	void CalculateNextMove();

};