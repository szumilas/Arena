#include "TurboBeePlayer.h"

void TurboBeePlayer::Initialize(TurboBeeGame* TurboBee, char newSign)
{
	game = TurboBee;
	sign = newSign;
}

std::list<TurboBeePlayer::Position> TurboBeePlayer::GetOponentsPositions()
{
	std::list<Position> positions;

	for (const auto& player : game->GetPlayers())
	{
		auto turboBeePlayer = dynamic_cast<TurboBeePlayer*>(player.get());

		if (this != turboBeePlayer)
		{
			positions.push_back({ turboBeePlayer->x, turboBeePlayer->y });
		}
	}

	return positions;
}
