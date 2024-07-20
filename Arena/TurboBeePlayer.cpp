#include "TurboBeePlayer.h"

void TurboBeePlayer::Initialize(TurboBeeGame* TurboBee, char newSign)
{
	game = TurboBee;
	sign = newSign;
}

std::list<TurboBeePlayer::BeeDetail> TurboBeePlayer::GetOponentsDetails()
{
	std::list<BeeDetail> positions;

	for (const auto& player : game->GetPlayers())
	{
		auto turboBeePlayer = dynamic_cast<TurboBeePlayer*>(player.get());

		if (this != turboBeePlayer)
		{
			positions.push_back({{ turboBeePlayer->x, turboBeePlayer->y }, turboBeePlayer->bag, turboBeePlayer->points});
		}
	}

	return positions;
}
