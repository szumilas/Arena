#include "TurboSnakePlayer.h"

void TurboSnakePlayer::Move()
{
	auto move = GetMove();
	switch (move)
	{
	case 1:
		y--;
		break;

	case 2:
		++x;
		break;

	case 3:
		++y;
		break;

	case 4:
		x--;
		break;

	default:
		break;
	}

	if (x > 19)
		x = 19;
	if (x < 0)
		x = 0;
	if (y > 19)
		y = 19;
	if (y < 0)
		y = 0;
}

void TurboSnakePlayer::Initialize(TurboSnakeGame* TurboSnake)
{
	game = TurboSnake;
}

TurboSnakeOutput TurboSnakePlayer::GetMove()
{
	return 0;
}