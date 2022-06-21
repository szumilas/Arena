#pragma once

#include "TurboFrogPlayer.h"

class TurboFrogPlayerBigFish : public TurboFrogPlayer
{
public:
	template<typename ...Args>
	TurboFrogPlayerBigFish(const Args&... args) : TurboFrogPlayer(args...) {}

private:
	void CalculateNextMove();
};