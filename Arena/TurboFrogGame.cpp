#include "TurboFrogGame.h"
#include "TurboFrogPlayer.h"

#include "Printer.h"

#include <iostream>
#include <Windows.h>
#include <string>
#include <sstream>
#include <iomanip>

void TurboFrogGame::Initialize()
{
	InitializeKeysMap();

	Printer::ShowConsoleCursor(hConsole, false);

	memset(map, ' ', mapWidth * mapHeight - 1);

	for (int q = 0; q < mapWidth * mapHeight; q++)
	{
		colors[q] = defaultMapColor;
	}

	char sign = 'A';
	for (auto& player : players)
	{
		auto turboFrogPlayer = dynamic_cast<TurboFrogPlayer*>(player.get());

		turboFrogPlayer->Initialize(this, sign);

		const auto randomX = rand() % mapWidth;
		const auto randomY = rand() % mapHeight;

		turboFrogPlayer->SetPosition(randomX, randomY);
		SetMapElement(randomX, randomY, turboFrogPlayer->sign);
		SetMapColor(randomX, randomY, Color::Black | Color::BG_LightYellow);

		sign++;
	}

	PrintPanel();
}

void TurboFrogGame::InitializeKeysMap()
{
	std::initializer_list<int> supportedKeys = { 'E', 'S', 'P', 'R', 'Y', 'N', '-', '=', 'S',
		VK_ADD, // +
		VK_SUBTRACT, // -
		VK_SHIFT, // shift
		VK_OEM_PLUS, // plus
		VK_OEM_MINUS, // minus
	};

	for (auto key : supportedKeys)
	{
		keys.insert({key, false});
	}
}

void TurboFrogGame::PrintPanel()
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

	PrintMenuText();
}

void TurboFrogGame::PrintMenuText(std::string menuText)
{
	menuText.resize(gameWidth - 4);
	WriteConsoleOutputCharacterA(hConsole, menuText.c_str(), static_cast<DWORD>(menuText.size()), { 2, mapHeight + 3 }, &dwBytesWritten);
}

void TurboFrogGame::PrintIntro()
{
	if (mapWidth < 88)
	{
		Printer::PrintCenter(hConsole, mapWidth, mapHeight, 5
			, "Turbo Frog"
		);
	}
	else
	{
		Printer::PrintCenter(hConsole, mapWidth, mapHeight, 0
			, " _______ __   __ ______   _______ _______           _______ ______   _______ _______ "
			, "|       |  | |  |    _ | |  _    |       |         |       |    _ | |       |       |"
			, "|_     _|  | |  |   | || | |_|   |   _   |         |    ___|   | || |   _   |    ___|"
			, "  |   | |  |_|  |   |_||_|       |  | |  |         |   |___|   |_||_|  | |  |   | __ "
			, "  |   | |       |    __  |  _   ||  |_|  |         |    ___|    __  |  |_|  |   ||  |"
			, "  |   | |       |   |  | | |_|   |       |         |   |   |   |  | |       |   |_| |"
			, "  |___| |_______|___|  |_|_______|_______|         |___|   |___|  |_|_______|_______|"
		);

		if (mapHeight > 43)
		{
			Printer::PrintCenter(hConsole, mapWidth, mapHeight, 10
				, "                                                                                "
				, "                  &RRRR&                                 @RRRR@                 "
				, "            @MTjk%%%%%%%%kliMR                     @M|!k%%%%%%%%kljM&           "
				, "          Ml%%%%%%%%%%%%%%%%%%jj&               @Ml%%%%%%%%%%%%%%%%%%lI&        "
				, "        Mk%%%%%jg@      @gp%%%%%%jB           @%%%%%%%jgg    & @gp%%%%%m]&      "
				, "      @j%%%%kg  &&&&&&&&&&& W%%%%%%8         Nk%%%%kg &&&&&&&&&&&& @g%%%%kR     "
				, "     @k%%%%] &&&&&&&&&&&&&&&& @%%%%%jFTT%MTTT%%%%%g &&&&&&&&&&&&&&&& @%%%%%%    "
				, "     j%%%%] &&&&&&&PMfR &&&&&&&@%%%%%%%%%%%m%%%%%#&&&&&&& PMMR &&&&&&&@%%%%%    "
				, "    @%%%%%&&&&&&&P      ]&&&&&& @%%%%m%%%%%%%%%%% &&&&&&F      T&&&&&& m%%%%]   "
				, "    [%%%%%&&&&&&&L       &&&&&&&W%%%%%%%%%%%%%%%%&&&&&&&C      j&&&&&&&H%%%%]   "
				, "     %%%%% &&&&&& w    a &&&&&&@k%%%%%%%%%%m%%%%m &&&&&& w    g &&&&&&@m%%%%    "
				, "     W%%%%k &&&&&&&&&&&&&&&&&& %%%%%%%%%%%%%%%%%%j&&&&&&&&&&&&&&&&&&&@%%%%%j    "
				, "      @%%%%k% &&&&&&&&&&&&&&&Nj%%%%%%%%%%%%%%%%%%%kB&&&&&&&&&&&&&&& Mk%%%%j     "
				, "      @%%%%%%k%  &&&&&&&& @%i%%%%%%%%%%%%%%%%%%%%%%%j%R &&&&&&&& R%j%%%%%%      "
				, "     @j%%%%%%%%%%j{j%%%{j%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%j{j%%{{jm%%%%%%%%%k&    "
				, "    @%%%%%%%m%%%%%%%%%%%%%%%%m%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%m    "
				, "   @%%%%%%%%%%%%%%%%%%%%m%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%mm%%%%%%%%%%%%%%%%%%%%&  "
				, "   M%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%j  "
				, "   m%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  "
				, "   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  "
				, "   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  "
				, "   m%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%& "
				, "   @%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%hjj%%%%H%j%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%]  "
				, "    Mm%%%%%%%%%%%%%%%%%%%%%%%%%%%%%pjj]%%%@jjj%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%k   "
				, "    &|%m%%%%%%%%%%%%%%%%%%%%%%%%%%%%H%%%%%%%H%%%%%%%%%%%%%%%%%%%%%%%%%%%%%@j    "
				, "      |{%H%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%HK}|     "
				, "       W|jj%%m%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%mHM}jjg      "
				, "         @ljjlj%U%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%HM}jjjjg        "
				, "           W|jjjjj!jj%U%m%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%mmHH%ljjjjjj|g          "
				, "             &g|jjjjjjjjjljj%M%H%U%%H%%%%mmH%%HUUHMM%}j!jjjjjjjjjjg@            "
				, "                &w|jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj|g                "
				, "                    &Wg|jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj|g@                    "
				, "                          N@wg||jjjjjjjjjjjjjjjjjj|lgg@                         "
			);
		}
		
	}
	PrintMenuText("Start game? [Y/N]");

	acceptAction = [&]() { SetState(State::Battle); this->PrintMenuText(); };
	denyAction = [&]() { SetState(State::GameOver); };
}

void TurboFrogGame::PrintStats()
{
	auto offset = static_cast<short>((mapWidth - 2) / players.size());

	short x = 1;

	for (const auto& player : players)
	{
		auto turboFrogPlayer = dynamic_cast<TurboFrogPlayer*>(player.get());

		std::string text;

		text += turboFrogPlayer->sign;
		text += " - [";

		std::ostringstream ss;
		ss << std::setw(4) << std::setfill(' ') << turboFrogPlayer->points;
		std::string points(ss.str());

		if (turboFrogPlayer->points >= 10'000)
			points = "WON!";

		text += points;
		text += "] ";
		text += turboFrogPlayer->teamName;

		text = text.substr(0, offset - 2);

		WriteConsoleOutputCharacterA(hConsole, text.c_str(), static_cast<DWORD>(text.size()), { x + 1, mapHeight + 1 }, &dwBytesWritten);

		x += offset;
	}
}

void TurboFrogGame::GenerateNewBonusPoints()
{
	if (rand() % 100 > 50 && GetBonusPoints().size() < 50)
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

void TurboFrogGame::UpdatePlayersPosition()
{
	for (auto& player : players)
	{
		auto turboFrogPlayer = dynamic_cast<TurboFrogPlayer*>(player.get());

		int newX = turboFrogPlayer->x;
		int newY = turboFrogPlayer->y;

		switch (turboFrogPlayer->nextMove)
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
			SetMapElement(turboFrogPlayer->x, turboFrogPlayer->y, ' ');
			SetMapColor(turboFrogPlayer->x, turboFrogPlayer->y, defaultMapColor);

			SetMapElement(newX, newY, turboFrogPlayer->sign);
			SetMapColor(newX, newY, Color::Black | Color::BG_LightYellow);

			turboFrogPlayer->x = newX;
			turboFrogPlayer->y = newY;
		}

	}
}

void TurboFrogGame::CalculateCollisions()
{
	for (auto& player : players)
	{
		auto turboFrogPlayer = dynamic_cast<TurboFrogPlayer*>(player.get());

		auto pointTaken = std::find_if(bonusPoints.begin(), bonusPoints.end(), [&](const auto& point)
			{
				return turboFrogPlayer->x == point.x && turboFrogPlayer->y == point.y;
			});

		if (pointTaken != bonusPoints.end())
		{
			turboFrogPlayer->AddPoints(pointTaken->value);
			bonusPoints.erase(pointTaken);
		}
	}
}

void TurboFrogGame::Update()
{
	UpdatePlayersPosition();
	CalculateCollisions();
	GenerateNewBonusPoints();
	UpdateUserInput();
	CheckWhoWon();
}

void TurboFrogGame::CheckWhoWon()
{
	for (auto& player : players)
	{
		auto turboFrogPlayer = dynamic_cast<TurboFrogPlayer*>(player.get());

		if (turboFrogPlayer->points > 10'000)
		{
			SetState(State::Pause);

			PrintMenuText("Player " + turboFrogPlayer->teamName + " won! Would you like to restart the game? [Y/N]");

			acceptAction = [&]() { this->RestartGame(); SetState(State::Battle); this->PrintMenuText(); };
			denyAction = [&]() { SetState(State::GameOver); };
		}
	}
}

void TurboFrogGame::UpdateUserInput()
{
	if (acceptAction == nullptr && denyAction == nullptr)
	{
		if (keys.at('R'))
		{
			PrintMenuText("Are you sure you want to restart the game? [Y/N]");

			acceptAction = [&]() { this->RestartGame(); this->PrintMenuText(); };
			denyAction = [&]() { this->PrintMenuText(); };
		}
		if (keys.at('P'))
		{
			PrintMenuText("Game paused. Resume? [Y]");
			SetState(State::Pause);

			acceptAction = [&]() { SetState(State::Battle); this->PrintMenuText(); };
		}
		if (keys.at('E'))
		{
			PrintMenuText("Are you sure you want to exit the game? [Y/N]");

			acceptAction = [&]() { SetState(State::GameOver); };
			denyAction = [&]() { this->PrintMenuText(); };
		}
		if (keys.at('S'))
		{
			if (GetState() == State::Simulation)
			{
				PrintMenuText("Are you sure you want to turn off simulation mode? [Y/N]");

				acceptAction = [&]() { SetState(State::Battle); this->PrintMenuText(); };
				denyAction = [&]() { this->PrintMenuText(); };
			}
			else
			{
				PrintMenuText("Are you sure you want to use simulation mode? [Y/N]");

				acceptAction = [&]() { SetState(State::Simulation); Printer::ClearBuffer(hConsole, 0, 0, mapWidth * mapHeight); this->PrintMenuText(); };
				denyAction = [&]() { this->PrintMenuText(); };
			}
		}
		if (keys.at(VK_ADD) || keys.at(VK_SHIFT) && keys.at(VK_OEM_PLUS) )
		{
			PrintMenuText("Are you sure you want to increase speed of the game? [Y/N]");

			acceptAction = [&]() { IncreaseGameSpeed(); this->PrintMenuText(); };
			denyAction = [&]() { this->PrintMenuText(); };
		}
		if (keys.at(VK_SUBTRACT) || !keys.at(VK_SHIFT) && keys.at(VK_OEM_MINUS))
		{
			PrintMenuText("Are you sure you want to decrease speed of the game? [Y/N]");

			acceptAction = [&]() { DecreaseGameSpeed(); this->PrintMenuText(); };
			denyAction = [&]() { this->PrintMenuText(); };
		}
	}

	if (keys.at('Y'))
	{
		if (acceptAction != nullptr)
		{
			acceptAction();
		}
		denyAction = nullptr;
		acceptAction = nullptr;
	}
	if (keys.at('N'))
	{
		if (denyAction != nullptr)
		{
			denyAction();
		}
		denyAction = nullptr;
		acceptAction = nullptr;
	}
}

void TurboFrogGame::RestartGame()
{
	memset(map, ' ', mapWidth * mapHeight - 1);

	for (int q = 0; q < mapWidth * mapHeight; q++)
	{
		colors[q] = defaultMapColor;
	}

	for (auto& player : players)
	{
		auto turboFrogPlayer = dynamic_cast<TurboFrogPlayer*>(player.get());

		const auto randomX = rand() % mapWidth;
		const auto randomY = rand() % mapHeight;

		turboFrogPlayer->SetPosition(randomX, randomY);
		SetMapElement(randomX, randomY, turboFrogPlayer->sign);
		SetMapColor(randomX, randomY, Color::Black | Color::BG_LightYellow);

		turboFrogPlayer->points = 0;
	}
}

void TurboFrogGame::Print()
{
	switch (GetState())
	{
	case State::Intro:
		PrintIntro();
		break;
	default:
		Game::Print();
	case State::Simulation:
		PrintStats();
		break;
	}
}

std::map<int, bool>& TurboFrogGame::GetKeyMap()
{
	return keys;
}