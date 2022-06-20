#pragma once

#include "Game.h"
#include "Printer.h"

struct BonusPoint
{
	int x{};
	int y{};
	int value{};
};

class TurboFrogGame : public Game
{
public:
	template<typename ...Args>
	TurboFrogGame(const Args&... args) : Game(args...) {}

	inline auto LocateBonusPoints() const { return &bonusPoints; }
	void Update();
	void CheckWhoWon();
	void UpdateUserInput();
	void Print();

	inline std::list<BonusPoint>& GetBonusPoints() { return bonusPoints; }

private:
	virtual void Initialize();
	void InitializeKeysMap();
	void GenerateNewBonusPoints();
	void UpdatePlayersPosition();
	void CalculateCollisions();
	void PrintPanel();
	void PrintStats();
	void PrintMenuText(std::string menuText = "[P] Pause [R] Restart [E] Exit [+] Speed++ [-] Speed-- [S] Simulation");
	std::map<int, bool>& GetKeyMap() final;
	void RestartGame();

private:
	std::list<BonusPoint> bonusPoints;

	int defaultMapColor = BG_LightAqua;

	std::map<int, bool> keys;

	std::function<void()> acceptAction = nullptr;
	std::function<void()> denyAction = nullptr;
};