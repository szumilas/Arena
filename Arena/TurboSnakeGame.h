#pragma once

#include "Game.h"
#include "Printer.h"

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
	virtual void Print();
	Game::State GetState() final;

	inline std::list<BonusPoint>& GetBonusPoints() { return bonusPoints; }

private:
	virtual void Initialize();
	void GenerateNewBonusPoints();
	void UpdatePlayersPosition();
	void CalculateCollisions();

private:
	std::list<BonusPoint> bonusPoints;

	int defaultMapColor = BG_LightAqua;
};