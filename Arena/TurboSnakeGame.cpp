#include "TurboSnakeGame.h"
#include "TurboSnakePlayer.h"

#include "Printer.h"

#include <iostream>


void TurboSnakeGame::Initialize()
{
	Printer::ShowConsoleCursor(false);

	for (auto& player : players)
	{
		dynamic_cast<TurboSnakePlayer*>(player.get())->Initialize(this);

		dynamic_cast<TurboSnakePlayer*>(player.get())->SetPosition(rand() % gameWidth, rand() % gameHeight);
	}

	system("CLS");

	for (int q = 0; q < gameHeight; ++q)
	{
		Printer::Gotoxy(gameWidth, q);
		std::cout << "|";
	}

	Printer::Gotoxy(0, gameHeight);

	for (int q = 0; q < gameWidth; ++q)
	{
		std::cout << "-";
	}

	std::cout << "+";
}

void TurboSnakeGame::MakeMove(const TurboSnakeOutput& move)
{
	
}

void TurboSnakeGame::Update()
{
	if (rand() % 100 > 75)
	{
		bonusPoints.push_back({ rand() % gameWidth, rand() % gameHeight, rand() % 9 + 1 });
	}

	for (auto& player : players)
	{
		auto turboSnakePlayer = dynamic_cast<TurboSnakePlayer*>(player.get());

		auto pointTaken = std::find_if(bonusPoints.begin(), bonusPoints.end(), [&](const auto& point)
			{
				return turboSnakePlayer->x == point.x && turboSnakePlayer->y == point.y;
			});

		if (pointTaken != bonusPoints.end())
		{
			turboSnakePlayer->AddPoints(pointTaken->value);
			bonusPoints.erase(pointTaken);
		}
	}
}

void TurboSnakeGame::Print()
{
	for (const auto& pointToCleaned : toBeCleaned)
	{
		Printer::Gotoxy(pointToCleaned.first, pointToCleaned.second);
		std::cout << " ";
	}

	toBeCleaned.clear();

	for (auto& player : players)
	{
		auto turboSnakePlayer = dynamic_cast<TurboSnakePlayer*>(player.get());

		Printer::Gotoxy(turboSnakePlayer->x, turboSnakePlayer->y);
		std::cout << static_cast<char>(219);

		toBeCleaned.push_back({ turboSnakePlayer->x, turboSnakePlayer->y });
	}

	for (const auto& bonusPoint : bonusPoints)
	{
		Printer::Gotoxy(bonusPoint.x, bonusPoint.y);
		std::cout << bonusPoint.value;
	}

	Printer::Gotoxy(0, gameHeight + 1);

	for (auto& player : players)
	{
		auto turboSnakePlayer = dynamic_cast<TurboSnakePlayer*>(player.get());

		
		std::cout << "Points: " << turboSnakePlayer->points << std::endl;

		toBeCleaned.push_back({ turboSnakePlayer->x, turboSnakePlayer->y });
	}
}

Game::State TurboSnakeGame::GetState()
{
	

	return Game::State::Battle;
}