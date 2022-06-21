#include "TurboFrogPlayerBigFish.h"

void TurboFrogPlayerBigFish::CalculateNextMove()
{
	int destinationX = 0;
	int destinationY = 0;

	int minDistance = 10000;

	auto calculateDistance = [myX = GetMyX(), myY = GetMyY()](int pointX, int pointY)
	{
		return abs(myX - pointX) + abs(myY - pointY);
	};

	for (const auto& bonusPoint : GetBonusPoints())
	{
		if (bonusPoint.value > 5)
		{
			if (auto newDistance = calculateDistance(bonusPoint.x, bonusPoint.y);
				minDistance > newDistance)
			{
				minDistance = newDistance;
				destinationX = bonusPoint.x;
				destinationY = bonusPoint.y;
			}
		}
	}

	if (GetMyX() > destinationX)
	{
		nextMove = 3;
		return;
	}
	if (GetMyX() < destinationX)
	{
		nextMove = 1;
		return;
	}

	if (GetMyY() > destinationY)
	{
		nextMove = 4;
		return;
	}
	if (GetMyY() < destinationY)
	{
		nextMove = 2;
		return;
	}
}
