#include "FootballPlayer_Team2.h"

void FootballPlayer_Team2::FindClosestFootballerToBall()
{
	double closestDistanceToBall = 10000;

	for (int i = 0; i < NoOfFootballers(); ++i)
	{
		if (auto currDist = CalculateDistance(GetMyFootballer(i), GetBallCoordinates());
			currDist < closestDistanceToBall)
		{
			closestDistanceToBall = currDist;
			closestToBall = i;
		}
	}
}

int FootballPlayer_Team2::FindClosestFootballerToFootballer(int id, double minDist, bool excludeGoalkeeper, bool preferAtack)
{
	double bestValue = 10000;

	int closestToFootballer{};

	for (int i = 0; i < NoOfFootballers(); ++i)
	{
		if (i == id)
			continue;

		if (excludeGoalkeeper && i == 0)
			continue;

		auto currDist = CalculateDistance(GetMyFootballer(i), GetMyFootballer(id));
		if (currDist < minDist)
			continue;

		auto atackCoeficient = (GetMyFootballer(i).x - GetMyFootballer(id).x) / currDist * preferAtack;

		auto totalValue = currDist - atackCoeficient * 5;

		if (totalValue < bestValue);
		{
			bestValue = totalValue;
			closestToFootballer = i;
		}
	}

	return closestToFootballer;
}

void FootballPlayer_Team2::SetGoalkeeperMove()
{
	//initialization
	static Coordinates defaultPosition = { 5, GetMapHeight() / 2 };

	static int minY = GetGoalRange().first;
	static int maxY = GetGoalRange().second;

	//outputs
	Coordinates targetPosition;

	//data
	auto ballPosition = GetBallCoordinates();
	auto distanceToball = CalculateDistance(GetMyFootballer(0), ballPosition);

	//calculation

	if (distanceToball < 10)
	{
		targetPosition.y = ballPosition.y;
		targetPosition.x = GetMyFootballer(0).x;
	}
	else if (distanceToball < 20)
	{
		targetPosition = (defaultPosition + ballPosition) / 2;
	}
	else
	{
		targetPosition = (defaultPosition * 5 + ballPosition) / 6;
	}

	if (targetPosition.y > maxY)
		targetPosition.y = maxY;
	if (targetPosition.y < minY)
		targetPosition.y = minY;

	SetTargetPositionForFootballer(0, targetPosition);

	if (closestToBall == 0)
	{
		SetTryKick(GetMyFootballer(FindClosestFootballerToFootballer(0, 15)));
	}
}

void FootballPlayer_Team2::SetDefenceMove()
{
	//initialization
	static auto defaultPosition = [&](int id) -> Coordinates
	{
		return { GetMapWidth() / 4 - 3, (((id - 1) % 4)) * GetMapHeight() / 6 + GetMapHeight() / 6};
	};

	//data
	auto ballPosition = GetBallCoordinates();

	//calculation
	for (int i = 1; i <= 4; ++i)
	{
		//outputs
		Coordinates targetPosition;

		auto distanceToball = CalculateDistance(GetMyFootballer(i), ballPosition);

		if (distanceToball < 15)
		{
			targetPosition = ballPosition;
		}
		else if (distanceToball < 30)
		{
			targetPosition = (defaultPosition(i) + ballPosition) / 2;
		}
		else
		{
			targetPosition = (defaultPosition(i) * 4 + ballPosition) / 5;
		}

		SetTargetPositionForFootballer(i, targetPosition);
	}

	if (closestToBall >= 1 && closestToBall <= 4)
	{
		SetTryKick(GetMyFootballer(FindClosestFootballerToFootballer(closestToBall, 15)));
	}
}

void FootballPlayer_Team2::SetMidfieldMove()
{

	//initialization
	static auto defaultPosition = [&](int id) -> Coordinates
	{
		return { GetMapWidth() / 2 - 2, (((id - 1) % 4)) * GetMapHeight() / 6 + GetMapHeight() / 6};
	};

	//data
	auto ballPosition = GetBallCoordinates();

	//calculation
	for (int i = 5; i <= 8; ++i)
	{
		//outputs
		Coordinates targetPosition;

		auto distanceToball = CalculateDistance(GetMyFootballer(i), ballPosition);

		if (distanceToball < 15)
		{
			targetPosition = ballPosition;
		}
		else if (distanceToball < 30)
		{
			targetPosition = (defaultPosition(i) * 2 + ballPosition) / 3;
		}
		else
		{
			targetPosition = (defaultPosition(i) * 4 + ballPosition) / 5;
		}

		SetTargetPositionForFootballer(i, targetPosition);
	}

	if (closestToBall >= 5 && closestToBall <= 8)
	{
		SetTryKick(GetMyFootballer(FindClosestFootballerToFootballer(closestToBall, 15)));
	}
}

void FootballPlayer_Team2::SetAtackMove()
{

	//initialization
	static auto defaultPosition = [&](int id) -> Coordinates
	{
		return { GetMapWidth() * 0.75 + 2, (((id - 1) % 2)) * GetMapHeight() / 3 + GetMapHeight() / 3 };
	};

	//data
	auto ballPosition = GetBallCoordinates();

	//calculation
	for (int i = 9; i <= 10; ++i)
	{
		//outputs
		Coordinates targetPosition;

		auto distanceToball = CalculateDistance(GetMyFootballer(i), ballPosition);

		if (distanceToball < 10)
		{
			targetPosition = ballPosition;
		}
		else if (distanceToball < 20)
		{
			targetPosition = (defaultPosition(i) * 2 + ballPosition) / 3;
		}
		else
		{
			targetPosition = (defaultPosition(i) * 4 + ballPosition) / 5;
		}

		SetTargetPositionForFootballer(i, targetPosition);
	}

	if (closestToBall >= 9 && closestToBall <= 10)
	{
		if (CalculateDistance(GetMyFootballer(closestToBall), { GetMapWidth(), GetMapHeight() / 2 }) > 40)
		{
			SetTryKick(GetMyFootballer(FindClosestFootballerToFootballer(closestToBall, 15)));
		}
		else
		{
			SetTryKick({ GetMapWidth(), closestToBall == 9 ? GetGoalRange().first + 1 : GetGoalRange().second - 1 });
		}
	}
}

void FootballPlayer_Team2::CalculateNextMove()
{
	FindClosestFootballerToBall();

	SetGoalkeeperMove();
	SetDefenceMove();
	SetMidfieldMove();
	SetAtackMove();
}
