#pragma once

#include "Player.h"

#include <list>
#include <map>
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

	Game(Strategy strategy, int width, int height);
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
	virtual void UpdateUserInput();
	virtual void Move();
	virtual void GetKeyPressed();
	virtual std::map<int, bool>& GetKeyMap();

	void TurnBasedMove();
	void RealTimeMove();

protected:

	enum class State
	{
		GameOver = 0,
		Battle,
		Pause,
		Restart,
		Simulation,
		Intro,
	};

	inline char GetMapElement(int x, int y) { if (x >= mapWidth || x < 0 || y >= mapHeight || y < 0) return 0; else return map[y * gameWidth + x]; }
	inline int GetMapWidth() { return mapWidth; }
	inline int GetMapHeight() { return mapHeight; }
	inline void SetMapElement(int x, int y, char value) { map[y * gameWidth + x] = value; }
	inline void SetMapColor(int x, int y, int newColor) { colors[y * gameWidth + x] = newColor; }
	virtual void Print();
	inline void SetState(State newState) { state = newState; }
	inline State GetState() { return state; }
	inline void IncreaseGameSpeed() { duration /= 1.1f; }
	inline void DecreaseGameSpeed() { duration *= 1.1f; }

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
	float duration = 50;
	State state = State::Intro;

	std::map<int, bool> keys;
};
