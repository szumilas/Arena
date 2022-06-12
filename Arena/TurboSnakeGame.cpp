#include "TurboSnakeGame.h"
#include "TurboSnakePlayer.h"

#include "Printer.h"

#include <iostream>
#include <Windows.h>

void TurboSnakeGame::Initialize()
{
	Printer::ShowConsoleCursor(hConsole, false);

	memset(map, ' ', gameWidth * gameHeight - 1);

	for (int q = 0; q < gameWidth * gameHeight; q++)
	{
		colors[q] = defaultMapColor;
	}

	for (auto& player : players)
	{
		auto turboSnakePlayer = dynamic_cast<TurboSnakePlayer*>(player.get());

		turboSnakePlayer->Initialize(this);

		const auto randomX = rand() % gameWidth;
		const auto randomY = rand() % gameHeight;

		turboSnakePlayer->SetPosition(randomX, randomY);
		SetMapElement(randomX, randomY, turboSnakePlayer->sign);
		SetMapColor(randomX, randomY, Color::Black | Color::BG_LightYellow);
	}
}

void TurboSnakeGame::GenerateNewBonusPoints()
{
	if (rand() % 100 > 1)
	{
		const auto randomX = rand() % gameWidth;
		const auto randomY = rand() % gameHeight;

		if (GetMapElement(randomX, randomY) == ' ')
		{
			const auto randomValue = rand() % 9 + 1;
			bonusPoints.push_back({ randomX, randomY, randomValue });
			SetMapElement(randomX, randomY, '0' + randomValue);

			switch (randomValue)
			{
			case 1:
			case 2:
			case 3:
				SetMapColor(randomX, randomY, Color::Black | Color::BG_LightGreen);
				break;
			case 4:
			case 5:
			case 6:
				SetMapColor(randomX, randomY, Color::Black | Color::BG_Yellow);
				break;
			default:
				SetMapColor(randomX, randomY, Color::Black | Color::BG_LightRed);
			}
		}
	}
}

void TurboSnakeGame::UpdatePlayersPosition()
{
	for (auto& player : players)
	{
		auto turboSnakePlayer = dynamic_cast<TurboSnakePlayer*>(player.get());

		int newX = turboSnakePlayer->x;
		int newY = turboSnakePlayer->y;

		switch (turboSnakePlayer->nextMove)
		{
		case 1:
			newX++;
			break;
		case 2:
			newY++;
			break;
		case 3:
			newX--;
			break;
		case 4:
			newY--;
			break;
		}

		if (newX >= gameWidth)
			newX = gameWidth - 1;
		if (newX < 0)
			newX = 0;
		if (newY >= gameHeight)
			newY = gameHeight - 1;
		if (newY < 0)
			newY = 0;

		if (auto element = GetMapElement(newX, newY);
			'1' <= element && element <= '9' || element == ' ')
		{
			SetMapElement(turboSnakePlayer->x, turboSnakePlayer->y, ' ');
			SetMapColor(turboSnakePlayer->x, turboSnakePlayer->y, defaultMapColor);

			SetMapElement(newX, newY, turboSnakePlayer->sign);
			SetMapColor(newX, newY, Color::Black | Color::BG_LightYellow);

			turboSnakePlayer->x = newX;
			turboSnakePlayer->y = newY;
		}

	}
}

void TurboSnakeGame::CalculateCollisions()
{
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

void TurboSnakeGame::Update()
{
	UpdatePlayersPosition();
	CalculateCollisions();
	GenerateNewBonusPoints();
}

Game::State TurboSnakeGame::GetState()
{
	return Game::State::Battle;
}

void TurboSnakeGame::Print()
{
	Game::Print();
}