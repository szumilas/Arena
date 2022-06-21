#pragma once

#include "TurboFrogPlayer.h"

class TurboFrogPlayerBigFishSmart : public TurboFrogPlayer
{
public:
	template<typename ...Args>
	TurboFrogPlayerBigFishSmart(const Args&... args) : TurboFrogPlayer(args...) {}

private:
	void CalculateNextMove();
};