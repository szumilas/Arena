#pragma once

#include "FootballPlayer.h"

class FootballPlayer_Team_TEMPLATE : public FootballPlayer
{
public:
	template<typename ...Args>
	FootballPlayer_Team_TEMPLATE(const Args&... args) : FootballPlayer(args...) { }

private:
	void CalculateNextMove();

};