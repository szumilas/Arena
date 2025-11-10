#include "FootballPlayer_Team3.h"

// SetTargetPositionForFootballer(int i, Coordinates newPosition)

void FootballPlayer_Team3::CalculateNextMove()
{
	//--------------------------------------------------------------
	//INITIAL POSITIONS
	//--------------------------------------------------------------
	// 
	//goalkeeper
	SetTargetPositionForFootballer(0, { 5, GetMapHeight() / 2 });
	//defence
	SetTargetPositionForFootballer(1, { GetMapWidth() / 5, GetMapHeight() / 4 * 1 });
	SetTargetPositionForFootballer(2, { GetMapWidth() / 5, GetMapHeight() / 4 * 2 });
	SetTargetPositionForFootballer(3, { GetMapWidth() / 5, GetMapHeight() / 4 * 3 });
	//midfield
	SetTargetPositionForFootballer(4, { GetMapWidth() / 2, GetMapHeight() / 5 * 1 });
	SetTargetPositionForFootballer(5, { GetMapWidth() / 2, GetMapHeight() / 5 * 2 });
	SetTargetPositionForFootballer(6, { GetMapWidth() / 2, GetMapHeight() / 5 * 3 });
	SetTargetPositionForFootballer(7, { GetMapWidth() / 2, GetMapHeight() / 5 * 4 });
	//atack
	SetTargetPositionForFootballer(8, { GetMapWidth() / 4 * 3, GetMapHeight() / 4 * 1 });
	SetTargetPositionForFootballer(9, { GetMapWidth() / 4 * 3, GetMapHeight() / 4 * 2 });
	SetTargetPositionForFootballer(10, { GetMapWidth() / 4 * 3, GetMapHeight() / 4 * 3 });

	//--------------------------------------------------------------
	//STRATEGY FOR ATACKING BALL
	//--------------------------------------------------------------

	auto closestFootballerToBall = [&]()
	{
		auto closestFootballer = 0;
		auto closestDistance = 9999999.;
		for (int i = 1; i <= NoOfFootballers(); ++i)
		{
			if (auto dist = CalculateDistance(GetMyFootballer(i), GetBallCoordinates());
				dist < closestDistance)
			{
				closestDistance = dist;
				closestFootballer = i;
			}
		}

		return closestFootballer;
	}();

	//closest to ball goes to ball
	SetTargetPositionForFootballer(closestFootballerToBall, GetBallCoordinates());

	//--------------------------------------------------------------
	//STRATEGY FOR KICKING THE BALL
	//--------------------------------------------------------------

	if (closestFootballerToBall < NoOfFootballers() - 1)
	{
		//pass ball to next footballer
		SetTryKick(GetMyFootballer(closestFootballerToBall + 1));
	}
	else
	{
		//try to score the goal
		SetTryKick({ GetMapWidth(), GetGoalRange().first + rand() % static_cast<int>(GetGoalRange().second - GetGoalRange().first) });
	}
}
