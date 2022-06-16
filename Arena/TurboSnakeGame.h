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
	virtual void UpdateUserInput();
	virtual void Print();

	inline std::list<BonusPoint>& GetBonusPoints() { return bonusPoints; }

private:
	virtual void Initialize();
	void GenerateNewBonusPoints();
	void UpdatePlayersPosition();
	void CalculateCollisions();
	void PrintPanel();
	void PrintStats();
	void PrintMenuText(std::string menuText = "[P] Pause    [R] Restart    [E] Exit");
	std::map<int, bool>& GetKeyMap() final;
	void RestartGame();

private:
	std::list<BonusPoint> bonusPoints;

	int defaultMapColor = BG_LightAqua;

	std::map<int, bool> keys = { {'S', false}, {'P', false}, {'R', false} , {'Y', false} , {'N', false} };
};