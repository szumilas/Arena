#pragma once

#include "TurboFrogPlayer.h"

class TurboFrogPlayerRandom : public TurboFrogPlayer
{
public:
	template<typename ...Args>
	TurboFrogPlayerRandom(const Args&... args) : TurboFrogPlayer(args...) {}

private:
	void CalculateNextMove();
};