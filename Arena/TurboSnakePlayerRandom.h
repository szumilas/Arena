#pragma once

#include "TurboSnakePlayer.h"

class TurboSnakePlayerRandom : public TurboSnakePlayer
{
public:
	template<typename ...Args>
	TurboSnakePlayerRandom(const Args&... args) : TurboSnakePlayer(args...) {}

private:
	TurboSnakeOutput GetMove();
};