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

	void Update();
	void CheckWhoWon();
	void UpdateUserInput();
	void Print();

	inline std::list<BonusPoint>& GetBonusPoints() { return bonusPoints; }
	inline std::list<std::unique_ptr<Player>>& GetPlayers() { return players; }
	inline char GetMapElement(int x, int y) { return Game::GetMapElement(x, y); }
	inline int GetMapWidth() { return Game::GetMapWidth(); }
	inline int GetMapHeight() { return Game::GetMapHeight(); }

private:
	virtual void Initialize();
	void InitializeKeysMap();
	void GenerateNewBonusPoints();
	void UpdatePlayersPosition();
	void CalculateCollisions();
	void PrintPanel();
	void PrintStats();
	void PrintIntro();
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