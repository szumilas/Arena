#include "TurboSnakeGame.h"
#include "TurboSnakePlayer.h"

#include "Printer.h"

#include <iostream>
#include <Windows.h>
#include <string>

void TurboSnakeGame::Initialize()
{
	Printer::ShowConsoleCursor(hConsole, false);

	memset(map, ' ', mapWidth * mapHeight - 1);

	for (int q = 0; q < mapWidth * mapHeight; q++)
	{
		colors[q] = defaultMapColor;
	}

	for (auto& player : players)
	{
		auto turboSnakePlayer = dynamic_cast<TurboSnakePlayer*>(player.get());

		turboSnakePlayer->Initialize(this);

		const auto randomX = rand() % mapWidth;
		const auto randomY = rand() % mapHeight;

		turboSnakePlayer->SetPosition(randomX, randomY);
		SetMapElement(randomX, randomY, turboSnakePlayer->sign);
		SetMapColor(randomX, randomY, Color::Black | Color::BG_LightYellow);
	}

	PrintPanel();
}

void TurboSnakeGame::PrintPanel()
{
	std::string panel;

	auto offset = (mapWidth - 2) / players.size();

	panel += static_cast<char>(201);
	for (int q = 0; q < players.size() - 1; ++q)
	{
		panel += std::string(offset - 1, static_cast<char>(205));
		panel += static_cast<char>(203);
	}
	panel += std::string(mapWidth - 2 - offset * (players.size() - 1), static_cast<char>(205));
	panel += static_cast<char>(187);

	panel += static_cast<char>(186);
	for (int q = 0; q < players.size() - 1; ++q)
	{
		panel += std::string(offset - 1, ' ');
		panel += static_cast<char>(186);
	}
	panel += std::string(mapWidth - 2 - offset * (players.size() - 1), ' ');
	panel += static_cast<char>(186);


	panel += static_cast<char>(204);
	for (int q = 0; q < players.size() - 1; ++q)
	{
		panel += std::string(offset - 1, static_cast<char>(205));
		panel += static_cast<char>(202);
	}
	panel += std::string(mapWidth - 2 - offset * (players.size() - 1), static_cast<char>(205));
	panel += static_cast<char>(185);

	panel += static_cast<char>(186);
	panel += std::string(mapWidth - 2, ' ');
	panel += static_cast<char>(186);

	panel += static_cast<char>(200);
	panel += std::string(mapWidth - 2, static_cast<char>(205));
	panel += static_cast<char>(188);

	WriteConsoleOutputAttribute(hConsole, &std::vector<WORD>(mapWidth * panelHeight, Color::BG_BrightWhite | Color::Black).front(), mapWidth * panelHeight, { 0, mapHeight }, &dwBytesWritten);
	WriteConsoleOutputCharacterA(hConsole, panel.c_str(), mapWidth * panelHeight, { 0, mapHeight }, &dwBytesWritten);
}

void TurboSnakeGame::PrintStats()
{
	auto offset = (mapWidth - 2) / players.size();

	short x = 1;

	for (const auto& player : players)
	{
		auto turboSnakePlayer = dynamic_cast<TurboSnakePlayer*>(player.get());

		std::string text;

		text += turboSnakePlayer->sign;
		text += " - ";
		text += std::to_string(turboSnakePlayer->points);

		WriteConsoleOutputCharacterA(hConsole, text.c_str(), text.size(), { x + 1, mapHeight + 1 }, &dwBytesWritten);

		x += offset;
	}
}

void TurboSnakeGame::GenerateNewBonusPoints()
{
	if (rand() % 100 > 90)
	{
		const auto randomX = rand() % mapWidth;
		const auto randomY = rand() % mapHeight;

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

		if (newX >= mapWidth)
			newX = mapWidth - 1;
		if (newX < 0)
			newX = 0;
		if (newY >= mapHeight)
			newY = mapHeight - 1;
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
	PrintStats();
	Game::Print();
}