#pragma once

#include "TurboFrogPlayer.h"

class TurboFrogPlayerGreedy : public TurboFrogPlayer
{
public:
	template<typename ...Args>
	TurboFrogPlayerGreedy(const Args&... args) : TurboFrogPlayer(args...) {}

private:
	void CalculateNextMove();
};