#pragma once

#include "Player.h"

#include <list>
#include <memory>
#include <functional>
#include <Windows.h>

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

	Game(Strategy strategy, int duration, int width, int height);
	virtual ~Game();

	virtual void Start();

	template<typename T, typename ...Args>
	void AddPlayer(const Args&... args)
	{
		players.push_back(std::make_unique<T>(args...));
	}

private:
	virtual void MainLoop();
	virtual void Initialize();
	virtual void Update();
	virtual void Move();
	virtual State GetState();

	void TurnBasedMove();
	void RealTimeMove();

protected:

	inline char& GetMapElement(int x, int y) { return map[y * gameWidth + x]; }
	inline void SetMapElement(int x, int y, char value) { map[y * gameWidth + x] = value; }
	inline void SetMapColor(int x, int y, int newColor) { colors[y * gameWidth + x] = newColor; }
	virtual void Print();

protected:
	std::list<std::unique_ptr<Player>> players;

	DWORD dwBytesWritten = 0;
	HANDLE hConsole;

	const int gameWidth;
	const int gameHeight;

	const int panelHeight = 5;
	const int mapWidth;
	const short mapHeight;

	char* map;
	WORD* colors;

private:

	Strategy strategy;
	int duration;
};
