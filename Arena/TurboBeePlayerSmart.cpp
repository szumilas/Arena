#include "TurboBeePlayerSmart.h"

int CalculateDistance(const auto& p1, const auto& p2)
{
	return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

bool TurboBeePlayerSmart::IsOponetCloser(int x, int y, int distance)
{
	for (const auto& oponent : GetOponentsDetails())
	{
		if (CalculateDistance(Position{ oponent.position.x, oponent.position.y }, Position{x, y}) < distance && oponent.bagValue != 10)
			return true;
	}

	return false;
}

void TurboBeePlayerSmart::CalculateNextMove()
{
	//--------------------------------------------
	// Algorithm:
	// Goes to the closest flower only when no other bee is around
	//--------------------------------------------

	std::vector<Position> blockedPositions;

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


		for (const auto& flower : GetFlowers())
		{
			if (auto newDistance = CalculateDistance(Position{GetMyX(), GetMyY()}, Position{ flower.x, flower.y });
				minDistance > newDistance && flower.hasPollen && newDistance > 0
				&& !IsOponetCloser(flower.x, flower.y, newDistance))
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
