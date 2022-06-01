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
	virtual void Print();
	virtual void Update();
	void MakeMove(const TurboSnakeOutput&);
	Game::State GetState() final;

private:
	virtual void Initialize();

private:

	//char board[3][3] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };

	std::list<BonusPoint> bonusPoints;
	std::list<std::pair<int, int>> toBeCleaned;

	int gameWidth = 50;
	int gameHeight = 20;

};