#include "Game.h"
#include "Printer.h"

#include <chrono>
#include <Windows.h>
#include <string>

Game::Game(Strategy strategy, int width, int height)
	: strategy(strategy), gameWidth(width), gameHeight(height), mapWidth(width), mapHeight(height - panelHeight)
{
	map = new char[mapWidth * mapHeight]();
	colors = new WORD[mapWidth * mapHeight]();

	hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
}

Game::~Game()
{
	delete[] map;
	delete[] colors;
}

void Game::Start()
{
	if (!players.size())
	{
		exit(-1);
	}
	duration /= players.size();
	srand(time(NULL));
	Initialize();
	MainLoop();
}

void Game::Initialize()
{

}

void Game::MainLoop()
{
	while (state != State::GameOver)
	{
		auto t_start = std::chrono::high_resolution_clock::now();

		switch (state)
		{
		case State::Intro:
			Print();
			GetKeyPressed();
			UpdateUserInput();
			break;
		case State::Battle:
		case State::Simulation:
		{
			GetKeyPressed();
			Move();
			Update();
			Print();
			break;
		}
		case State::Pause:
		{
			GetKeyPressed();
			UpdateUserInput();
		}
		}
		auto t_end = std::chrono::high_resolution_clock::now();

		double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();

		if (duration > elapsed_time_ms && state != State::Simulation)
		{
			Sleep(duration - elapsed_time_ms);
		}
		
		SetConsoleTitle(std::to_wstring(static_cast<int>(1000.0 / elapsed_time_ms)).c_str());
	}
}

void Game::GetKeyPressed()
{
	auto& keys = GetKeyMap();
	for (auto& key : keys)
	{
		key.second = GetAsyncKeyState(key.first) & 0x8000;
	}
}

std::map<int, bool>& Game::GetKeyMap()
{
	return keys;
}

void Game::Update()
{

}

void Game::UpdateUserInput()
{

}

void Game::Print()
{
	WriteConsoleOutputAttribute(hConsole, colors, mapWidth * mapHeight, { 0, 0 }, &dwBytesWritten);
	WriteConsoleOutputCharacterA(hConsole, map, mapWidth * mapHeight, { 0, 0 }, &dwBytesWritten);
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

void Game::TurnBasedMove()
{
	static size_t i = 0;
	size_t x = 0;

	for (auto& player : players)
	{
		player->ResetNextMove();
	}

	for (auto& player : players)
	{
		if (x < i)
		{
			++x;
			continue;
		}

		player->CalculateNextMove();
		break;
	}

	++i;
	i = i % players.size();
}

void Game::RealTimeMove()
{
	for (auto& player : players)
	{
		player->CalculateNextMove();
	}
}