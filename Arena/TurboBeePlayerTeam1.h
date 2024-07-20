#pragma once

#include "TurboBeePlayer.h"

class TurboBeePlayerTeam1 : public TurboBeePlayer
{
public:
	template<typename ...Args>
	TurboBeePlayerTeam1(const Args&... args) : TurboBeePlayer(args...) {}

private:
	void CalculateNextMove();
};