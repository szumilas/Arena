#include "TurboBeeGame.h"
#include "TurboBeePlayer.h"

#include "Printer.h"

#include <iostream>
#include <Windows.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>

constexpr auto pointsToWin = 100;
constexpr auto maxNumberOfFlowers = 200;

void TurboBeeGame::Initialize()
{
	InitializeKeysMap();

	Printer::ShowConsoleCursor(hConsole, false);

	memset(map, ' ', mapWidth * mapHeight - 1);

	for (int q = 0; q < mapWidth * mapHeight; q++)
	{
		colors[q] = defaultMapColor;
	}

	for (int ix = -1; ix < 2; ++ix)
		for (int iy = -1; iy < 2; ++iy)
		{
			int X = mapWidth / 2 + ix;
			int Y = mapHeight / 2 + iy;
			PrintBeeHouse(X, Y);
			beeHouses.push_back({ mapWidth / 2 + ix, mapHeight / 2 + iy });
		}

	char sign = 'A';
	for (auto& player : players)
	{
		auto turboBeePlayer = dynamic_cast<TurboBeePlayer*>(player.get());

		turboBeePlayer->Initialize(this, sign);

		const auto newX = mapWidth / 2 - 1 + (sign - 'A') % 3;
		const auto newY = mapHeight / 2 - 1 + (sign - 'A') / 3;

		turboBeePlayer->SetPosition(newX, newY);
		SetMapElement(newX, newY, turboBeePlayer->sign);
		SetMapColor(newX, newY, Color::Black | Color::BG_LightYellow);
		turboBeePlayer->elementPlayerCovers = '#';

		sign++;
	}

	GenerateFlowers();

	PrintPanel();
}

void TurboBeeGame::PrintBeeHouse(int x, int y)
{
	SetMapColor(x, y, Color::Black | Color::BG_Yellow);
	SetMapElement(x, y, '#');
}

void TurboBeeGame::PrintFlower(const Flower& flower)
{
	if (flower.hasPollen)
	{
		SetMapColor(flower.x, flower.y, Color::LightYellow | Color::BG_LightRed);
		SetMapElement(flower.x, flower.y, 'o');
	}
	else
	{
		SetMapColor(flower.x, flower.y, Color::White | Color::BG_LightPurple);
		SetMapElement(flower.x, flower.y, 'x');
	}

}

void TurboBeeGame::GenerateFlowers()
{
	auto noOfFlowersToGenerate = maxNumberOfFlowers;

	while (noOfFlowersToGenerate > 0)
	{
		auto generateRandom = [&](int limit)
		{
			const auto radius = limit / 2;

			std::vector<int> probability;

			for (int i = 0; i < limit / 2; ++i)
			{
				if(i < limit / 2 * 3 / 4)
					probability.push_back(i);
				else
					probability.push_back(limit / 2 * 3 / 4 - (i - limit / 2 * 3 / 4));
			}

			int randomDistance{};
			int randomToCheck = rand() % (limit / 2);

			do
			{
				if (probability[randomToCheck] < rand() % (limit / 2))
				{
					randomDistance = randomToCheck;
					break;
				}

				randomToCheck = rand() % (limit / 2);
			} while (true);

			const auto sign = rand() % 2 * 2 - 1;

			return limit / 2 + sign * (limit / 2 - randomDistance);

			const auto result = limit / 2 + sign * (radius - (rand() % radius) * (rand() % radius) / radius);
			const auto resultEqual = limit / 2 + sign * (rand() % radius);

			return result;
			return (3 * result + resultEqual) / 4;
		};

		const int randomX = generateRandom(mapWidth);
		const int randomY = generateRandom(mapHeight);

		if (GetMapElement(randomX, randomY) == ' ')
		{
			Flower newFlower{ randomX, randomY, true};
			flowers.push_back(newFlower);


			PrintFlower(newFlower);

			--noOfFlowersToGenerate;
		}
	}
}

void TurboBeeGame::InitializeKeysMap()
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
		keys.insert({ key, false });
	}
}

void TurboBeeGame::PrintPanel()
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

void TurboBeeGame::PrintMenuText(std::string menuText)
{
	menuText.resize(gameWidth - 4);
	WriteConsoleOutputCharacterA(hConsole, menuText.c_str(), static_cast<DWORD>(menuText.size()), { 2, mapHeight + 3 }, &dwBytesWritten);
}

void TurboBeeGame::PrintIntro()
{
	if (mapWidth < 88)
	{
		Printer::PrintCenter(hConsole, mapWidth, mapHeight, 5
			, "Turbo Bee"
		);
	}
	else
	{
		Printer::PrintCenter(hConsole, mapWidth, mapHeight, 0
			, " _______ __   __ ______   _______ _______           _______  _______ _______ "
			, "|       |  | |  |    _ | |  _    |       |         |  _    ||  _____|  _____|"
			, "|_     _|  | |  |   | || | |_|   |   _   |         | |_|   || |_____| |_____ "
			, "  |   | |  |_|  |   |_||_|       |  | |  |         |       || ______| ______|"
			, "  |   | |       |    __  |  _   ||  |_|  |         |  _   ||| |     | |      "
			, "  |   | |       |   |  | | |_|   |       |         | |_|   || |_____| |_____ "
			, "  |___| |_______|___|  |_|_______|_______|         |_______||_______|_______|"
		);

		if (mapHeight > 43)
		{
			Printer::PrintCenter(hConsole, mapWidth, mapHeight, 10
,"                                         .^~!!!~^.                  "
,"                                     :!YGBBGPPPGBBGY~               "
,"                                   ~5#B57^.     .:7P#G!             "
,"                                 :5&G7.       :~7?JYB&&P7~:         "
,"                                :G&J.      ^YGBGPYJ?77?YPBBG?:      "
,"              :!~              .P&J     .!G#G?^.         .^JB#J.    "
,"             !B#J              J&P.    !G&5~                .Y&G:   "
,"  .??^      !&B^              ^##~   ^P&P~                    Y&P   "
,"  .JG#P!    5&P7??7!^:        5&5  .J#B7                      ^##^  "
,"     ~B&?!5G###&&&&##BP?^    :##~ ^G&5:                       :##~  "
,"      ~###&############&#5^  ?&G.?##7                         J&G.  "
,"     :P##################&#! P&Y5&P:                         ?&B~   "
,"     P&####################B!B###J                        .!P&P^    "
,"    ~#######################B##&G7!~^:.            ..:^!?5B#P!      "
,"    !&#########################BBB###BGGGPPP555PPGGGGBGGPJ!:        "
,"    :B########################P~~~Y#####YJ5B&BY7~~~^^:.             "
,"     !#######################5~~~Y#####?^^~G###GJ:                  "
,"      ^P#&##################Y~~~5####B7^~!G###&P5BY:                "
,"        !5B#&&#############J~~~P####B7^^7B####P~^!B#7               "
,"          .~?Y5P##########J^~~P####G!^^7B####5~~~J##&Y              "
,"                !########?^~!G####G!^^?#####Y~~~Y####&Y             "
,"                 ^G&###B7^^!G####P~~^?#####Y~~~5####B5&!            "
,"                  .?B&B!^^7B####P~~^J#####J^~~P####B!~BP            "
,"                    :YB5!7B####5~~~Y#####?^~~P####G!^^P#:           "
,"                      :JG#&###Y~~~Y####B?^~!G####G!^~^5&J           "
,"                        .75#&P~^~5####B7^^!B####P~^~7Y#&B:          "
,"                           :75GPG&###G!^^7B####P7J5GPY?~:           "
,"                              :~?5PB#PYYY#&###BP5J!:                "
,"                                   .:^~!!!~~^:..                    "
			);
		}

	}
	PrintMenuText("Start game? [Y/N]");

	acceptAction = [&]() { SetState(State::Battle); this->PrintMenuText(); };
	denyAction = [&]() { SetState(State::GameOver); };
}

void TurboBeeGame::PrintStats()
{
	auto offset = static_cast<short>((mapWidth - 2) / players.size());

	short x = 1;

	for (const auto& player : players)
	{
		auto turboBeePlayer = dynamic_cast<TurboBeePlayer*>(player.get());

		std::string text;

		text += turboBeePlayer->sign;
		text += " - [";

		std::ostringstream ss;
		ss << std::setw(2) << std::setfill(' ') << turboBeePlayer->points << "|";
		ss << std::setw(2) << std::setfill(' ') << turboBeePlayer->bag;
		std::string points(ss.str());

		if (turboBeePlayer->points >= pointsToWin)
			points = " WON!";

		text += points;
		text += "] ";
		text += turboBeePlayer->teamName;

		text = text.substr(0, offset - 2);

		WriteConsoleOutputCharacterA(hConsole, text.c_str(), static_cast<DWORD>(text.size()), { x + 1, mapHeight + 1 }, &dwBytesWritten);

		x += offset;
	}
}

void TurboBeeGame::UpdatePlayersPosition()
{
	for (auto& player : players)
	{
		auto turboBeePlayer = dynamic_cast<TurboBeePlayer*>(player.get());

		int newX = turboBeePlayer->x;
		int newY = turboBeePlayer->y;

		switch (turboBeePlayer->nextMove)
		{
		case NEXTMOVE::RIGHT:
			newX++;
			break;
		case NEXTMOVE::DOWN:
			newY++;
			break;
		case NEXTMOVE::LEFT:
			newX--;
			break;
		case NEXTMOVE::UP:
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
			element == 'x' || element == 'o'
			|| element == '#' || element == ' ')
		{
			auto elementPlayerCovered = turboBeePlayer->elementPlayerCovers;
			turboBeePlayer->elementPlayerCovers = element;

			switch (elementPlayerCovered)
			{
			case 'x':
			case 'o':
			{
				const auto f = std::ranges::find_if(flowers, [&](const auto& f) { return f.x == turboBeePlayer->x && f.y == turboBeePlayer->y;  });
				PrintFlower(*f);
				break;
			}

			case '#':
				PrintBeeHouse(turboBeePlayer->x, turboBeePlayer->y);
				break;

			default:
				SetMapColor(turboBeePlayer->x, turboBeePlayer->y, defaultMapColor);
				SetMapElement(turboBeePlayer->x, turboBeePlayer->y, elementPlayerCovered);
				break;
			}

			SetMapElement(newX, newY, turboBeePlayer->sign);
			SetMapColor(newX, newY, Color::Black | Color::BG_LightYellow);

			turboBeePlayer->x = newX;
			turboBeePlayer->y = newY;
		}
		
		/*
		if (auto element = GetMapElement(newX, newY);
			'0' <= element && element <= '9' || element == ' ' || element == '+' || element == 'x' || element == 'o'
			|| element == '#')
		{

			bool flowerFound = false;

			for (auto& flower : flowers)
			{
				if (flower.x == turboBeePlayer->x &&
					flower.y == turboBeePlayer->y)
				{
					flowerFound = true;
					break;
				}
			}

			SetMapColor(turboBeePlayer->x, turboBeePlayer->y, defaultMapColor);

			if(flowerFound)
				PrintFlower(turboBeePlayer->x, turboBeePlayer->y, 0);
			else
				SetMapElement(turboBeePlayer->x, turboBeePlayer->y, element);



			SetMapElement(newX, newY, turboBeePlayer->sign);
			SetMapColor(newX, newY, Color::Black | Color::BG_LightYellow);

			turboBeePlayer->x = newX;
			turboBeePlayer->y = newY;
		}*/

	}
}

void TurboBeeGame::CalculateCollisions()
{
	for (auto& player : players)
	{
		auto turboBeePlayer = dynamic_cast<TurboBeePlayer*>(player.get());

		auto flowerVisited = std::find_if(flowers.begin(), flowers.end(), [&](const auto& point)
			{
				return turboBeePlayer->x == point.x && turboBeePlayer->y == point.y;
			});

		if (flowerVisited != flowers.end())
		{
			if (turboBeePlayer->bag < 10 && flowerVisited->hasPollen)
			{
				turboBeePlayer->AddPollenToBag();
				flowerVisited->hasPollen = false;
			}
		}

		if (IsBeeHouse(turboBeePlayer->x, turboBeePlayer->y))
		{
			turboBeePlayer->AddPoints(turboBeePlayer->GetBagValue());
			turboBeePlayer->ResetBag();
		}
	}
}

bool TurboBeeGame::IsBeeHouse(int x, int y)
{
	for (const auto& beeHouse : beeHouses)
	{
		if (beeHouse.x == x && beeHouse.y == y)
			return true;
	}

	return false;
}

void TurboBeeGame::BloomFlowers()
{
	for (auto& flower : flowers)
	{
		if (rand() % 10000 < 15)
		{
			flower.hasPollen = true;
			PrintFlower(flower);
		}
	}
}

void TurboBeeGame::Update()
{
	UpdatePlayersPosition();
	CalculateCollisions();
	BloomFlowers();
	UpdateUserInput();
	CheckWhoWon();
}

void TurboBeeGame::CheckWhoWon()
{
	for (auto& player : players)
	{
		auto turboBeePlayer = dynamic_cast<TurboBeePlayer*>(player.get());

		if (turboBeePlayer->points >= pointsToWin)
		{
			SetState(State::Pause);

			PrintMenuText("Player " + turboBeePlayer->teamName + " won! Would you like to restart the game? [Y/N]");

			acceptAction = [&]() { this->RestartGame(); SetState(State::Battle); this->PrintMenuText(); };
			denyAction = [&]() { SetState(State::GameOver); };
		}
	}
}

void TurboBeeGame::UpdateUserInput()
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
		if (keys.at(VK_ADD) || keys.at(VK_SHIFT) && keys.at(VK_OEM_PLUS))
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

void TurboBeeGame::RestartGame()
{
	memset(map, ' ', mapWidth * mapHeight - 1);
	flowers.clear();

	for (int q = 0; q < mapWidth * mapHeight; q++)
	{
		colors[q] = defaultMapColor;
	}

	std::ranges::for_each(beeHouses, [&](const auto& i) { PrintBeeHouse(i.x, i.y); });

	int count = 0;
	for (auto& player : players)
	{
		auto turboBeePlayer = dynamic_cast<TurboBeePlayer*>(player.get());

		const auto newX = mapWidth / 2 - 1 + count % 3;
		const auto newY = mapHeight / 2 - 1 + count / 3;

		turboBeePlayer->SetPosition(newX, newY);
		SetMapElement(newX, newY, turboBeePlayer->sign);
		SetMapColor(newX, newY, Color::Black | Color::BG_LightYellow);

		turboBeePlayer->points = 0;
		turboBeePlayer->bag = 0;
		turboBeePlayer->elementPlayerCovers = '#';

		++count;
	}

	GenerateFlowers();
}

void TurboBeeGame::Print()
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

std::map<int, bool>& TurboBeeGame::GetKeyMap()
{
	return keys;
}