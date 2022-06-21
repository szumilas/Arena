#pragma once

#include "TurboFrogPlayer.h"

class TurboFrogPlayerShy : public TurboFrogPlayer
{
public:
	template<typename ...Args>
	TurboFrogPlayerShy(const Args&... args) : TurboFrogPlayer(args...) {}

private:
	void CalculateNextMove();
};