#pragma once

#include "Game.h"



using TurboSnakeOutput = int;

struct BonusPoint
{
	int x{};
	int y{};
	int value{};
};

class TurboSnakeGame : public Game
{
public:
	template<typename ...Args>
	TurboSnakeGame(const Args&... args) : Game(args...) {}

	inline auto LocateBonusPoints() const { return &bonusPoints; }
	virtual void Update();
	Game::State GetState() final;

private:
	virtual void Initialize();
	void GenerateNewBonusPoints();
	void UpdatePlayersPosition();
	void CalculateCollisions();

private:
	std::list<BonusPoint> bonusPoints;


};