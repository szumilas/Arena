#include "TurboBeePlayerGreedy.h"

void TurboBeePlayerGreedy::CalculateNextMove()
{
	//--------------------------------------------
	// Algorithm:
	// Goes to the closest flower
	//--------------------------------------------

	int destinationX = 0;
	int destinationY = 0;

	if (GetBagValue() >= 10)
	{
		destinationX = GetMapWidth() / 2;
		destinationY = GetMapHeight() / 2;
	}
	else
	{

		int minDistance = 10000;

		auto calculateDistance = [myX = GetMyX(), myY = GetMyY()](int pointX, int pointY)
		{
			return abs(myX - pointX) + abs(myY - pointY);
		};

		for (const auto& flower : GetFlowers())
		{
			if (auto newDistance = calculateDistance(flower.x, flower.y);
				minDistance > newDistance && flower.hasPollen && newDistance > 0)
			{
				minDistance = newDistance;
				destinationX = flower.x;
				destinationY = flower.y;
			}
		}
	}

	if (GetMyX() > destinationX)
	{
		nextMove = NEXTMOVE::LEFT;
		return;
	}
	if (GetMyX() < destinationX)
	{
		nextMove = NEXTMOVE::RIGHT;
		return;
	}

	if (GetMyY() > destinationY)
	{
		nextMove = NEXTMOVE::UP;
		return;
	}
	if (GetMyY() < destinationY)
	{
		nextMove = NEXTMOVE::DOWN;
		return;
	}
}
