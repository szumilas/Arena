#include "TurboSnakePlayerGreedy.h"

void TurboSnakePlayerGreedy::CalculateNextMove()
{
	int destinationX = 0;
	int destinationY = 0;

	int minDistance = 10000;

	auto calculateDistance = [myX = x, myY = y](int pointX, int pointY)
	{
		return abs(myX - pointX) + abs(myY - pointY);
	};

	for (const auto& bonusPoint : game->GetBonusPoints())
	{
		if (auto newDistance =  calculateDistance(bonusPoint.x, bonusPoint.y);
			minDistance > newDistance)
		{
			minDistance = newDistance;
			destinationX = bonusPoint.x;
			destinationY = bonusPoint.y;
		}
	}

	if (x > destinationX)
	{
		nextMove = 3;
		return;
	}
	if (x < destinationX)
	{
		nextMove = 1;
		return;
	}

	if (y > destinationY)
	{
		nextMove = 4;
		return;
	}
	if (y < destinationY)
	{
		nextMove = 2;
		return;
	}
}
