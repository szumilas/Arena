#include <array>

#include "TurboFrogPlayerBigFishSmart.h"

void TurboFrogPlayerBigFishSmart::CalculateNextMove()
{
	//--------------------------------------------
	// Algorithm:
	// Goes to the closest bonus point with a
	// value greater than 5. In meantime, he
	// collects as many other bonus points as 
	// possible
	//--------------------------------------------

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

	std::array<int, 5> whatNext{};

	for (const auto& bonusPoint : GetBonusPoints())
	{
		if ((GetMyX() <= bonusPoint.x && bonusPoint.x <= destinationX || GetMyX() >= bonusPoint.x && bonusPoint.x >= destinationX)
			&& (GetMyY() <= bonusPoint.y && bonusPoint.y <= destinationY || GetMyY() >= bonusPoint.y && bonusPoint.y >= destinationY))
		{
			if (GetMyX() <= bonusPoint.x && bonusPoint.x <= destinationX)
			{
				if (GetMyX() < bonusPoint.x)
					whatNext[1] += bonusPoint.value;
			}
			if (GetMyX() >= bonusPoint.x && bonusPoint.x >= destinationX)
			{
				if (GetMyX() > bonusPoint.x)
					whatNext[3] += bonusPoint.value;
			}

			if (GetMyY() <= bonusPoint.y && bonusPoint.y <= destinationY)
			{
				if (GetMyY() < bonusPoint.y)
					whatNext[2] += bonusPoint.value;
			}
			if (GetMyY() >= bonusPoint.y && bonusPoint.y >= destinationY)
			{
				if (GetMyY() > bonusPoint.y)
					whatNext[4] += bonusPoint.value;
			}
		}
	}

	int max = 0;

	for (int q = 1; q <= 4; q++)
	{
		if (whatNext[q] > max)
		{
			max = whatNext[q];
			nextMove = q;
		}
	}
}
