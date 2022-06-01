#include "Game.h"

#include <chrono>
#include <Windows.h>

void Game::Start()
{
	srand(time(NULL));
	Initialize();
	MainLoop();
}

void Game::Initialize()
{

}

void Game::MainLoop()
{
	while (GetState() == State::Battle)
	{
		auto t_start = std::chrono::high_resolution_clock::now();
		Move();
		Update();
		Print();
		auto t_end = std::chrono::high_resolution_clock::now();

		double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();

		if (duration > elapsed_time_ms)
		{
			Sleep(duration - elapsed_time_ms);
		}
	}
}

void Game::Update()
{

}

void Game::Print()
{

}

void Game::Move()
{
	switch (strategy)
	{
	case Game::Strategy::TurnBased:
		TurnBasedMove();
		break;
	case Game::Strategy::RealTime:
		RealTimeMove();
		break;
	default:
		break;
	}
}

Game::State Game::GetState()
{
	return State::GameOver;
}

void Game::TurnBasedMove()
{
	static size_t i = 0;
	size_t x = 0;

	for (auto& player : players)
	{
		if (x < i)
		{
			++x;
			continue;
		}

		player->Move();
		break;
	}

	++i;
	i = i % players.size();
}

void Game::RealTimeMove()
{
	for (auto& player : players)
	{
		player->Move();
	}
}