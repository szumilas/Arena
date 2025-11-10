#include "FootballPlayer.h"

void FootballPlayer::Initialize(FootballGame* Football, int noOfFootballers)
{
	game = Football;

	ResetPlayers(noOfFootballers);
}

void FootballPlayer::ResetPlayers(int noOfFootballers)
{
	footballers.clear();

	for (int q = 0; q < noOfFootballers; ++q)
	{
		footballers.push_back({ {game->GetMapWidth() / 4.0 + away * game->GetMapWidth() / 2, game->GetMapHeight() / 2.0 - (noOfFootballers - 1) * 2 + static_cast<double>(q * 4)}, q == 10 ? 'A' : static_cast<char>(q + '0')});
	}
}

double FootballPlayer::CalculateDistance(const Coordinates& p1, const Coordinates& p2) const
{
	return game->CalculateDistance(p1, p2);
}


int FootballPlayer::GetMyGoals() const
{
	if (away)
		return game->GetScore().second;
	else
		return game->GetScore().first;
}

int FootballPlayer::GetOponentGoals() const
{
	if (away)
		return game->GetScore().first;
	else
		return game->GetScore().second;
}

Coordinates FootballPlayer::GetBallCoordinates() 
{
	Coordinates c = game->GetBall().current_position;

	if (away)
		c.x = static_cast<double>(GetMapWidth()) - c.x;

	return c;
}

void FootballPlayer::SetTryKick(const Coordinates c)
{
	TryKick = c;

	if(away)
		TryKick.x = static_cast<double>(GetMapWidth()) - TryKick.x;
};

Coordinates FootballPlayer::GetMyFootballer(int i)
{
	Coordinates c = footballers[i % footballers.size()].current_position;

	if(away)
		c.x = static_cast<double>(GetMapWidth()) - c.x;

	return c;
};

Coordinates FootballPlayer::GetOpponentFootballer(int i)
{
	FootballPlayer* opponent = nullptr;
	auto firstPlayer = dynamic_cast<FootballPlayer*>(game->GetPlayers().begin()->get());
	auto secondPlayer = dynamic_cast<FootballPlayer*>((++game->GetPlayers().begin())->get());

	if (firstPlayer == this)
		opponent = secondPlayer;
	else
		opponent = firstPlayer;

	Coordinates c = opponent->GetMyFootballer(i % footballers.size());

	c.x = static_cast<double>(GetMapWidth()) - c.x;

	return c;
};

void FootballPlayer::SetTargetPositionForFootballer(int i, Coordinates newPosition)
{
	if (away)
		footballers[i % footballers.size()].target_position.x = static_cast<double>(GetMapWidth()) - newPosition.x;
	else
		footballers[i % footballers.size()].target_position.x = newPosition.x;

	footballers[i % footballers.size()].target_position.y = newPosition.y;
}