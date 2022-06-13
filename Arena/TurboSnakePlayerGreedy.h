#pragma once

#include "TurboSnakePlayer.h"

class TurboSnakePlayerGreedy : public TurboSnakePlayer
{
public:
	template<typename ...Args>
	TurboSnakePlayerGreedy(const Args&... args) : TurboSnakePlayer(args...) {}

private:
	void CalculateNextMove();
};