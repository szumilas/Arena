#pragma once

#include "TurboBeePlayer.h"

class TurboBeePlayerGreedy : public TurboBeePlayer
{
public:
	template<typename ...Args>
	TurboBeePlayerGreedy(const Args&... args) : TurboBeePlayer(args...) {}

private:
	void CalculateNextMove();
};