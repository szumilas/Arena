#pragma once

#include "TurboBeePlayer.h"

class TurboBeePlayerSmart : public TurboBeePlayer
{
public:
	template<typename ...Args>
	TurboBeePlayerSmart(const Args&... args) : TurboBeePlayer(args...) {}

private:
	void CalculateNextMove();

	bool IsOponetCloser(int x, int y, int distance);
};