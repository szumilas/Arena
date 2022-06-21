#include "TurboFrogPlayerShy.h"

void TurboFrogPlayerShy::CalculateNextMove()
{
	//--------------------------------------------
	// Algorithm:
	// Goes to the closest bonus point, but bonus
	// point can't be achieved by any other
	// oponent
	//--------------------------------------------

	int destinationX = 0;
	int destinationY = 0;

	int minDistance = 10000;

	auto calculateDistance = [myX = GetMyX(), myY = GetMyY()](int pointX, int pointY)
	{
		return abs(myX - pointX) + abs(myY - pointY);
	};

	auto oponents = TurboFrogPlayerShy::GetOponentsPositions(this);

	for (const auto& bonusPoint : GetBonusPoints())
	{
		if (auto newDistance = calculateDistance(bonusPoint.x, bonusPoint.y);
			minDistance > newDistance)
		{
			bool okToTake = true;

			for (const auto& oponent : oponents)
			{
				auto oponentDistance = calculateDistance(oponent.x, oponent.y);

				if (oponentDistance < newDistance)
				{
					okToTake = false;
					break;
				}
			}

			if (okToTake)
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
