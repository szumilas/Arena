#pragma once

#include "Player.h"
#include "FootballGame.h"

class FootballPlayer : public Player
{
	friend class FootballGame;

public:
	FootballPlayer(std::string teamName) : teamName(teamName) {}

	inline int GetMapWidth() { return game->GetMapWidth(); }
	inline int GetMapHeight() { return game->GetMapHeight(); }
	Coordinates GetBallCoordinates();

	double CalculateDistance(const Coordinates& p1, const Coordinates& p2) const;
	int GetMyGoals() const;
	int GetOponentGoals() const;

protected:

	Coordinates GetMyFootballer(int i);
	Coordinates GetOpponentFootballer(int i);
	void SetTryKick(const Coordinates c);
	void SetTargetPositionForFootballer(int i, Coordinates newPosition);
	inline int NoOfFootballers() { return game->GetNoOfFootballers(); }
	inline std::pair<double, double> GetGoalRange() { return game->GetGoalRange(); }

private:
	Coordinates TryKick;
	void Initialize(FootballGame*, int noOfFootballers);
	void ResetPlayers(int noOfFootballers);
	bool away;

	std::string teamName;

	FootballGame* game = nullptr;

	std::vector<Footballer> footballers;
};