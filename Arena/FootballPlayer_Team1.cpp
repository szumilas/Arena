#include "FootballPlayer_Team1.h"

std::map<int, Coordinates> FootballPlayer_Team1::GetDefaultPositions()
{
	/*static*/ std::map<int, Coordinates> defaultPositions;

	if (!defaultPositions.empty())
		return defaultPositions;

	for (int i = 0; i < NoOfFootballers(); ++i)
	{
		Coordinates target;

		switch (i % 9)
		{
			//defence
		case 0:
		case 1:
		case 2:
			target.x = GetMapWidth() / 5;
			break;

			//midfield
		case 3:
		case 4:
		case 5:
			target.x = GetMapWidth() / 2;
			break;

			//atack
		case 6:
		case 7:
		case 8:
			target.x = GetMapWidth() / 5 * 4;
			break;
		}


		switch (i % 9)
		{
			//left
		case 0:
		case 5:
		case 6:
			target.y = GetMapHeight() / 5;
			break;

			//middle
		case 1:
		case 4:
		case 7:
			target.y = GetMapHeight() / 2;
			break;

			//right
		case 2:
		case 3:
		case 8:
			target.y = GetMapHeight() / 5 * 4;
			break;
		}

		target.x += rand() % 15 - 15;
		target.y += rand() % 5 - 5;

		defaultPositions[i] = target;
	}

	defaultPositions[0] = { 5, GetMapHeight() / 2 };

	return defaultPositions;
}

void FootballPlayer_Team1::CalculateNextMove()
{
	// goes to middle point
	if (false)
	{
		for (int i = 0; i < NoOfFootballers(); ++i)
		{
			SetTargetPositionForFootballer(i, {20,20});
		}
		return;
	}

	//--------------------------------------------
	// Algorithm:
	// Goes to the closest flower
	//--------------------------------------------

	auto bestDistToBall = 99999;

	int goesToBall = 0;

	for (int i = 0; i < NoOfFootballers(); ++i)
	{
		SetTargetPositionForFootballer(i, GetDefaultPositions()[i]);


		auto currDistToBall = CalculateDistance(GetMyFootballer(i), GetBallCoordinates());

		if (currDistToBall < bestDistToBall)
		{
			bestDistToBall = currDistToBall;
			goesToBall = i;
		}

		if (rand() % 1000 < 3)
		{
			const double nextX = rand() % GetMapWidth();
			const double nextY = rand() % GetMapHeight();

			SetTargetPositionForFootballer(i, { nextX, nextY });
		}
	}

	//if (away)
	//	return;

	//for (const auto& myFootballer : GetMyFootballers())
	//{
	//	auto currDistToBall = CalculateDistance(myFootballer.current_position, GetBallCoordinates());

	//	if (currDistToBall < bestDistToBall)
	//	{
	//		bestDistToBall = currDistToBall;
	//		goesToBall = &myFootballer;
	//	}

	//	if (rand() % 100 < 0)
	//	{
	//		const double nextX = rand() % GetMapWidth();
	//		const double nextY = rand() % GetMapHeight();

	//		SetTargetPosition(myFootballer, { nextX, nextY });
	//	}
	//	
	//	//SetTargetPosition(myFootballer, GetBallCoordinates());
	//}

	SetTargetPositionForFootballer(goesToBall, GetBallCoordinates());

	SetTryKick(GetMyFootballer((goesToBall + 1) % NoOfFootballers()));

	if (goesToBall == 8)
	{

		SetTryKick( {GetMapWidth() * 1.0, GetMapHeight() * 0.5 + rand() % 6 - 3});
	}

	auto x0 = GetOpponentFootballer(0);
}
