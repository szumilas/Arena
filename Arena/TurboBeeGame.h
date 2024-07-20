#pragma once

#include "Game.h"
#include "Printer.h"

struct Flower
{
	int x{};
	int y{};
	bool hasPollen{};
};

struct Position
{
	int x{};
	int y{};
};

enum class NEXTMOVE
{
	IDLE,
	RIGHT,
	DOWN,
	LEFT,
	UP,
};

class TurboBeeGame : public Game
{
public:
	template<typename ...Args>
	TurboBeeGame(const Args&... args) : Game(args...) {}

	void Update();
	void CheckWhoWon();
	void UpdateUserInput();
	void Print();

	inline std::list<Flower>& GetFlowers() { return flowers; }
	inline std::list<std::unique_ptr<Player>>& GetPlayers() { return players; }
	inline char GetMapElement(int x, int y) { return Game::GetMapElement(x, y); }
	inline int GetMapWidth() { return Game::GetMapWidth(); }
	inline int GetMapHeight() { return Game::GetMapHeight(); }
	bool IsBeeHouse(int x, int y);

private:
	virtual void Initialize();
	void InitializeKeysMap();
	void GenerateFlowers();
	void PrintFlower(const Flower& flower);
	void PrintBeeHouse(int x, int y);
	void UpdatePlayersPosition();
	void CalculateCollisions();
	void PrintPanel();
	void BloomFlowers();
	void PrintStats();
	void PrintIntro();
	void PrintMenuText(std::string menuText = "[P] Pause [R] Restart [E] Exit [+] Speed++ [-] Speed-- [S] Simulation");
	std::map<int, bool>& GetKeyMap() final;
	void RestartGame();

private:
	std::list<Flower> flowers;
	std::vector<Position> beeHouses;

	int defaultMapColor = BG_LightGreen;

	std::map<int, bool> keys;

	std::function<void()> acceptAction = nullptr;
	std::function<void()> denyAction = nullptr;
};