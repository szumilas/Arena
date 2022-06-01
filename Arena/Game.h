#pragma once

#include "Player.h"

#include <list>
#include <memory>
#include <functional>

class Game
{
public:

	enum class Strategy
	{
		TurnBased,
		RealTime,
	};

	enum class State
	{
		Battle,
		GameOver,
	};

	Game(Strategy strategy, int duration) : strategy(strategy), duration(duration) {}

	virtual void Start();

	template<typename T, typename ...Args>
	void AddPlayer(const Args&... args)
	{
		players.push_back(std::make_unique<T>(args...));
	}

private:
	virtual void MainLoop();
	virtual void Initialize();
	virtual void Print();
	virtual void Update();
	virtual void Move();
	virtual State GetState();

	void TurnBasedMove();
	void RealTimeMove();

protected:
	std::list<std::unique_ptr<Player>> players;

private:

	Strategy strategy;
	int duration;
};
