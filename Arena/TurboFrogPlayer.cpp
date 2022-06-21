#include "TurboFrogPlayer.h"

void TurboFrogPlayer::Initialize(TurboFrogGame* TurboFrog, char newSign)
{
	game = TurboFrog;
	sign = newSign;
}

std::list<TurboFrogPlayer::Position> TurboFrogPlayer::GetOponentsPositions(TurboFrogPlayer* myself)
{
	std::list<Position> positions;

	for (const auto& player : game->GetPlayers())
	{
		auto turboFrogPlayer = dynamic_cast<TurboFrogPlayer*>(player.get());

		if (myself != turboFrogPlayer)
		{
			positions.push_back({ turboFrogPlayer->x, turboFrogPlayer->y });
		}
	}

	return positions;
}
