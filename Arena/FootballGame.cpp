#include "FootballGame.h"
#include "FootballPlayer.h"

#include "Printer.h"
#include "Music.h"

#include <iostream>
#include <Windows.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cassert>

void FootballGame::Initialize()
{
	dynamic_cast<FootballPlayer*>(players.begin()->get())->away = false;
	dynamic_cast<FootballPlayer*>((++players.begin())->get())->away = true;

	InitializeKeysMap();

	Printer::ShowConsoleCursor(hConsole, false);

	memset(map, ' ', mapWidth * mapHeight - 1);

	SetDefaultMapColors();

	for (const auto& player : players)
		dynamic_cast<FootballPlayer*>(player.get())->Initialize(this, noOfFootballers);

	SetDefaultMap();

	ResetMapToDefault();

	PrintPanel();

}

void FootballGame::SetDefaultMap()
{
	//--------------------------------- OUTER LINES
	for (int q = 1; q < mapWidth - 1; ++q)
	{
		SetDefaultMapElement(q, 0, 196);
		SetDefaultMapElement(q, mapHeight - 1, 196);
	}

	for (int q = 1; q < mapHeight - 1; ++q)
	{
		SetDefaultMapElement(0, q, 179);
		SetDefaultMapElement(mapWidth - 1, q, 179);
		SetDefaultMapElement(mapWidth / 2, q, 179);
	}

	SetDefaultMapElement(0, 0, 218);
	SetDefaultMapElement(0, mapHeight - 1, 192);
	SetDefaultMapElement(mapWidth - 1, mapHeight - 1, 217);
	SetDefaultMapElement(mapWidth - 1, 0, 191);

	SetDefaultMapElement(mapWidth / 2, 0, 194);
	SetDefaultMapElement(mapWidth / 2, mapHeight - 1, 193);

	//-------------------------------- MIDDLE CIRCLE
	const auto radius = mapHeight / 5 / 2;
	for (int q = -radius; q <= radius; ++q)
	{
		SetDefaultMapElement(mapWidth / 2 + q, mapHeight / 2 - radius, 196);
		SetDefaultMapElement(mapWidth / 2 + q, mapHeight / 2 + radius, 196);

		SetDefaultMapElement(mapWidth / 2 - radius, mapHeight / 2 + q, 179);
		SetDefaultMapElement(mapWidth / 2 + radius, mapHeight / 2 + q, 179);
	}

	SetDefaultMapElement(mapWidth / 2 - radius, mapHeight / 2 - radius, 218);
	SetDefaultMapElement(mapWidth / 2 - radius, mapHeight / 2 + radius, 192);
	SetDefaultMapElement(mapWidth / 2 + radius, mapHeight / 2 + radius, 217);
	SetDefaultMapElement(mapWidth / 2 + radius, mapHeight / 2 - radius, 191);

	SetDefaultMapElement(mapWidth / 2, mapHeight / 2 - radius, 197);
	SetDefaultMapElement(mapWidth / 2, mapHeight / 2 + radius, 197);

	//----------------------------------- PENALTY AREA
	const auto penaltyAreaWidth = mapWidth / 8;
	const auto penaltyAreaHeight = mapHeight / 2;

	for (int q = 1; q < penaltyAreaWidth; ++q)
	{
		//left
		SetDefaultMapElement(q, mapHeight / 2 - penaltyAreaHeight / 2, 196);
		SetDefaultMapElement(q, mapHeight / 2 + penaltyAreaHeight / 2, 196);

		//right
		SetDefaultMapElement(mapWidth - 1 - q, mapHeight / 2 - penaltyAreaHeight / 2, 196);
		SetDefaultMapElement(mapWidth - 1 - q, mapHeight / 2 + penaltyAreaHeight / 2, 196);
	}

	for (int q = 1; q < penaltyAreaHeight; ++q)
	{
		//left
		SetDefaultMapElement(penaltyAreaWidth, mapHeight / 2 - penaltyAreaHeight / 2 + q, 179);
		//right
		SetDefaultMapElement(mapWidth - penaltyAreaWidth - 1, mapHeight / 2 - penaltyAreaHeight / 2 + q, 179);
	}

	//corners
	//left
	SetDefaultMapElement(penaltyAreaWidth, mapHeight / 2 - penaltyAreaHeight / 2, 191);
	SetDefaultMapElement(penaltyAreaWidth, mapHeight / 2 + penaltyAreaHeight / 2, 217);
	SetDefaultMapElement(0, mapHeight / 2 - penaltyAreaHeight / 2, 195);
	SetDefaultMapElement(0, mapHeight / 2 + penaltyAreaHeight / 2, 195);
	//right
	SetDefaultMapElement(mapWidth - penaltyAreaWidth - 1, mapHeight / 2 - penaltyAreaHeight / 2, 218);
	SetDefaultMapElement(mapWidth - penaltyAreaWidth - 1, mapHeight / 2 + penaltyAreaHeight / 2, 192);
	SetDefaultMapElement(mapWidth - 1, mapHeight / 2 - penaltyAreaHeight / 2, 180);
	SetDefaultMapElement(mapWidth - 1, mapHeight / 2 + penaltyAreaHeight / 2, 180);

	//circles
	for (int q = 0; q <= radius; ++q)
	{
		//left
		SetDefaultMapElement(penaltyAreaWidth + q, mapHeight / 2 - radius, 196);
		SetDefaultMapElement(penaltyAreaWidth + q, mapHeight / 2 + radius, 196);

		//right
		SetDefaultMapElement(mapWidth - penaltyAreaWidth - radius + q - 1, mapHeight / 2 - radius, 196);
		SetDefaultMapElement(mapWidth - penaltyAreaWidth - radius + q - 1, mapHeight / 2 + radius, 196);
	}

	SetDefaultMapElement(penaltyAreaWidth, mapHeight / 2 - radius, 195);
	SetDefaultMapElement(penaltyAreaWidth, mapHeight / 2 + radius, 195);

	SetDefaultMapElement(mapWidth - penaltyAreaWidth - 1, mapHeight / 2 - radius, 180);
	SetDefaultMapElement(mapWidth - penaltyAreaWidth - 1, mapHeight / 2 + radius, 180);

	for (int q = -radius; q <= radius; ++q)
	{
		SetDefaultMapElement(penaltyAreaWidth + radius, mapHeight / 2 + q, 179);
		SetDefaultMapElement(mapWidth - penaltyAreaWidth - radius - 1, mapHeight / 2 + q, 179);
	}

	SetDefaultMapElement(penaltyAreaWidth + radius, mapHeight / 2 - radius, 191);
	SetDefaultMapElement(penaltyAreaWidth + radius, mapHeight / 2 + radius, 217);

	SetDefaultMapElement(mapWidth - penaltyAreaWidth - radius - 1, mapHeight / 2 - radius, 218);
	SetDefaultMapElement(mapWidth - penaltyAreaWidth - radius - 1, mapHeight / 2 + radius, 192);

	//goal
	for (int q = -goalSize / 2; q <= goalSize / 2; ++q)
	{
		SetDefaultMapElement(0, mapHeight / 2 + q, 179);
		colors[(mapHeight / 2 + q) * gameWidth] = homeColor;

		SetDefaultMapElement(mapWidth - 1, mapHeight / 2 + q, 179);
		colors[(mapHeight / 2 + q) * gameWidth + mapWidth - 1] = awayColor;
	}
}

void FootballGame::SetDefaultMapColors()
{
	for (int q = 0; q < mapWidth * mapHeight; q++)
	{
		colors[q] = defaultMapColor;
	}

	for (int q = -goalSize / 2; q <= goalSize / 2; ++q)
	{
		colors[(mapHeight / 2 + q) * gameWidth] = homeColor;
		colors[(mapHeight / 2 + q) * gameWidth + mapWidth - 1] = awayColor;
	}
}

void FootballGame::ResetPlayers()
{
	for (const auto& player : players)
		dynamic_cast<FootballPlayer*>(player.get())->ResetPlayers(noOfFootballers);
}

void FootballGame::InitializeKeysMap()
{
	std::initializer_list<int> supportedKeys = { 'E', 'P', 'R', 'Y', 'N', 'Q', 'W', 'B', 'A', 'S'};

	for (auto key : supportedKeys)
	{
		keys.insert({ key, false });
	}
}

void FootballGame::PrintPanel()
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
	WriteConsoleOutputAttribute(hConsole, &std::vector<WORD>(1, homeColor).front(), 1, { 2, mapHeight + 1 }, &dwBytesWritten);
	WriteConsoleOutputAttribute(hConsole, &std::vector<WORD>(1, awayColor).front(), 1, { static_cast<short>(mapWidth / 2 + 1), mapHeight + 1 }, &dwBytesWritten);
	WriteConsoleOutputCharacterA(hConsole, panel.c_str(), mapWidth * panelHeight, { 0, mapHeight }, &dwBytesWritten);
	
	PrintMenuText();
}

void FootballGame::PrintMenuText(std::string menuText)
{
	menuText.resize(gameWidth - 4);
	WriteConsoleOutputCharacterA(hConsole, menuText.c_str(), static_cast<DWORD>(menuText.size()), { 2, mapHeight + 3 }, &dwBytesWritten);
}

void FootballGame::PrintIntro()
{
	if (mapWidth < 88)
	{
		Printer::PrintCenter(hConsole, mapWidth, mapHeight, 5
			, "Turbo Football"
		);
	}
	else
	{
		Printer::PrintCenter(hConsole, mapWidth, mapHeight, 0
			, "  _______         _             ______          _   _           _ _  "
			, " |__   __|       | |           |  ____|        | | | |         | | | "
			, "    | |_   _ _ __| |__   ___   | |__ ___   ___ | |_| |__   __ _| | | "
			, "    | | | | | '__| '_ \\ / _ \\  |  __/ _ \\ / _ \\| __| '_ \\ / _` | | | "
			, "    | | |_| | |  | |_) | (_) | | | | (_) | (_) | |_| |_) | (_| | | | "
			, "    |_|\\__,_|_|  |_.__/ \\___/  |_|  \\___/ \\___/ \\__|_.__/ \\__,_|_|_| "
		);

		if (mapHeight > 43)
		{
			Printer::PrintCenter(hConsole, mapWidth, mapHeight, 10
				, "              .#-------*:              "
				, "            @-:::::.:::::-@            "
				, "          @@@:...........:%--          "
				, "        @@@@@....     ....@.:-@        "
				, "       @@@@@:..:%-.  .:%@@@..::-       "
				, "      @@@@@.      .%@@@@@@@@:.::-      "
				, "     @@@@:         :@@@@@@@@@:.::-     "
				, "    @@@@:          .@@@@@@@@@@..:-%    "
				, "    @@@*           .@@@@@@@@@@@..:-    "
				, "   =::..            @@@@@@@@@@@@:::-   "
				, "   :....            @@@@@@@@@@@..:%-%  "
				, "  -:....            %@@@@@@@@@:....-@  "
				, "  -:...:           .=+@@@@@@@@.....:@  "
				, " #:..  -          .:   .:@@@@......:@@ "
				, " +:..  @         :.       .-:.......-@ "
				, " -:..  :.       :.         .#.......:@ "
				, " -:..  +@@@:.  -.          .-.......:@ "
				, " -:....@@@@@@@%.          ..........:@ "
				, " -:...@@@@@@@@@.         ....:......:% "
				, " -:...@@@@@@@@@.        .....#......:* "
				, " =:..-@@@@@@@@@:       ......%......:- "
				, " @:..@@@@@@@@@@@     ........-.....:@= "
				, " %-:.*@@@@@@@@@@  ...........#+....:-@ "
				, "  -:..@@@@@@@@@@............-@@@@..:-  "
				, "  =:..:@@@@@@@@@:..........=@@@@@@+:-  "
				, "   -:..*@@@@@@@@:%........%@@@@@@@:--  "
				, "   -::..*@@@@@.....=-....@@@@@@@@@:-   "
				, "    -:...:@:...........-@@@@@@@@@@-    "
				, "    @-:...-.............@@@@@@@@@-%    "
				, "     =-:..@.............*@@@@@@@@=     "
				, "      --:.-.............:@@@@@@@@      "
				, "       +-::..............@@@@@-=       "
				, "        @-:@:............::::-@        "
				, "          @@@:::.......::::--          "
				, "            @@@@-::::=-:--=            "
				, "              .@@@@----*:              "
			);
		}

	}
	PrintMenuText("Start game? [Y/N]");

	acceptAction = [&]() { SetState(State::Battle); this->PrintMenuText(); };
	denyAction = [&]() { SetState(State::GameOver); };
}

void FootballGame::PrintStats()
{
	static auto previousScore = GetScore();

	auto offset = static_cast<short>((mapWidth - 2) / players.size());

	short x = 1;

	for (const auto& player : players)
	{
		auto team = dynamic_cast<FootballPlayer*>(player.get());

		std::string text;

		text += "x ";
		text += team->teamName;
		text += " - ";

		std::ostringstream ss;
		ss << team->GetMyGoals();
		text += ss.str();

		if (team->away && team->GetMyGoals() > previousScore.second || !team->away && team->GetMyGoals() > previousScore.first)
		{
			text += " GOAL!";
		}
		else
		{
			text += "      ";
		}

		text = text.substr(0, offset - 2);

		WriteConsoleOutputCharacterA(hConsole, text.c_str(), static_cast<DWORD>(text.size()), { x + 1, mapHeight + 1 }, &dwBytesWritten);

		x += offset;
	}
	previousScore = GetScore();
}

bool FootballGame::UpdatePlayersPosition()
{
	static int ballKickedInterval = 0;

	bool away{};
	bool ballKicked{};

	double closestToBall = 99999;
	Coordinates kickTo = ball.target_position;

	for (const auto& player : players)
	{
		const auto team = dynamic_cast<FootballPlayer*>(player.get());

		int color = away ? awayColor : homeColor;

		for (auto& footballer : team->footballers)
		{
			// find the closest footballer to the ball
			if (auto diffToBall = CalculateDistance(footballer.current_position, ball.current_position);
				diffToBall < 1)
			{
				if (team->TryKick.x || team->TryKick.y)
				{
					if (closestToBall > diffToBall)
					{
						diffToBall = closestToBall;

						kickTo = team->TryKick;

						ballKicked = true;
					}
				}
			}

			// no movement
			if(CalculateDistance(footballer.current_position, footballer.target_position) < 1.0 / 3)
			{
				footballer.current_position = footballer.target_position;
				footballer.velocity = Coordinates{};
				elementsToPrint.insert({ {(footballer.current_position.x), (footballer.current_position.y) }, { footballer.item, color }
					});
				continue;
			}

			if (!(footballer.target_position.x == 0 && footballer.target_position.y == 0))
			{
				const auto diffX = footballer.target_position.x - footballer.current_position.x;
				const auto diffY = footballer.target_position.y - footballer.current_position.y;

				const auto total = pow(diffX * diffX + diffY * diffY, 0.5);

				footballer.velocity.x = diffX / total / 3;
				footballer.velocity.y = diffY / total / 3;
			}

			UpdateObjectAndPreparedToPrint(footballer, color);
		}

		away = true;

		team->TryKick = {};
	}

	if (ballKicked && ballKickedInterval > 3)
	{
		ball.target_position = kickTo;

		std::thread([]() {Beep(523, 100); }).detach();

		const auto ballDiffX = ball.target_position.x - ball.current_position.x;
		const auto ballDiffY = ball.target_position.y - ball.current_position.y;

		const auto total = pow(ballDiffX * ballDiffX + ballDiffY * ballDiffY, 0.5);

		if (total == NAN)
		{
			assert(false, "divide by 0");
		}
		else
		{
			ball.velocity.x = ballDiffX / total;
			ball.velocity.y = ballDiffY / total;
		}

		ballKickedInterval = 0;
	}

	++ballKickedInterval;

	return ballKicked;
}

double FootballGame::CalculateDistance(const Coordinates& p1, const Coordinates& p2) const
{
	return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

void FootballGame::UpdateObjectAndPreparedToPrint(Object& object, int color)
{
	if (object.current_position.x + object.velocity.x >= pitchWidth - 0.5 || object.current_position.x + object.velocity.x <= 0.5)
	{
		if (object.bounces)
			object.velocity.x *= -1;
		else
			object.velocity.x = 0;
	}
	if (object.current_position.y + object.velocity.y >= pitchHeight - 0.5 || object.current_position.y + object.velocity.y <= 0.5)
	{
		if (object.bounces)
			object.velocity.y *= -1;
		else
			object.velocity.y = 0;
	}

	object.current_position.x += object.velocity.x;
	object.current_position.y += object.velocity.y;

	//elementsToPrint.insert({ { round(object.current_position.x), round(object.current_position.y)}, {object.item , color} });
	elementsToPrint.insert({ { (object.current_position.x), (object.current_position.y)}, {object.item , color} });
}

void FootballGame::UpdateBall(bool ballKicked)
{
	if (!ballKicked)
	{
		ball.velocity.x *= frictionCoefficient;
		ball.velocity.y *= frictionCoefficient;
	}

	if (const auto goal = CheckGoal(); goal.first)
	{
		ResetPlayers();
		ball = defaultBall;
		ball.current_position.x += -goal.second * pitchWidth / 2 + pitchWidth / 4;

		SetDefaultMapColors();
		ResetMapToDefault();
		return;
	}

	UpdateObjectAndPreparedToPrint(ball, ballColor);
}

void FootballGame::PrepareToPrint()
{
	for (auto it = previousElementsToPrint.begin(); it != previousElementsToPrint.end(); )
	{
		int x = round(it->first.x);
		int y = round(it->first.y);
		auto color = defaultMapColor;
		auto item = GetDefaultMapElement(x, y);

		SetMapColor(x, y, defaultMapColor);
		SetMapElement(x, y, item);

		it = previousElementsToPrint.upper_bound(it->first);
	}

	for (auto it = elementsToPrint.begin(); it != elementsToPrint.end(); )
	{
		auto range = elementsToPrint.equal_range(it->first);


		int x = round(it->first.x);
		int y = round(it->first.y);
		auto color = it->second.second;

		if (elementsToPrint.count(it->first) > 1)
		{
			if (!std::all_of(range.first, range.second, [&](const auto& i) { return i.second.second == color || i.second.second == (Color::BrightWhite | Color::BG_Black); }))
				color = unknownColor;
		}

		auto item = it->second.first;

		if (elementsToPrint.count(it->first) > 1)
		{
			if (std::find_if(range.first, range.second, [](const auto& i) { return i.second.first == 'o'; }) != range.second)
				item = 'o';
			else if (std::all_of(range.first, range.second, [&](const auto& i) { return i.second.second == color; }))
				item = '?';
			else
				item = static_cast<char>(220);
		}

		SetMapColor(x, y, color);
		SetMapElement(x, y, item);

		it = elementsToPrint.upper_bound(it->first);
	}
}

void FootballGame::Update()
{
	previousElementsToPrint = elementsToPrint;
	elementsToPrint.clear();

	const auto ballKicked = UpdatePlayersPosition();
	UpdateBall(ballKicked);

	PrepareToPrint();

	UpdateUserInput();
	CheckWhoWon();
}

std::pair<bool, int> FootballGame::CheckGoal()
{
	std::pair<bool, int> goal{};
	if (ball.current_position.y + ball.velocity.y >= GetGoalRange().first && ball.current_position.y + ball.velocity.y <= GetGoalRange().second)
	{
		if (ball.current_position.x + ball.velocity.x >= pitchWidth - 0.5)
		{
			score.first++;
			goal.first = true;
			goal.second = 0;
		}
		else if (ball.current_position.x + ball.velocity.x <= 0.5)
		{
			score.second++;
			goal.first = true;
			goal.second = 1;
		}
	}

	if (goal.first)
	{
		PrintStats();
		PlayMusic();
	}

	return goal;
}

void FootballGame::CheckWhoWon()
{
	for (auto& player : players)
	{
		auto footballPlayer = dynamic_cast<FootballPlayer*>(player.get());

		if (footballPlayer->GetMyGoals() >= winningScore)
		{
			SetState(State::Pause);

			PrintMenuText("Player " + footballPlayer->teamName + " won! Would you like to restart the game? [Y/N]");

			acceptAction = [&]() { this->RestartGame(); SetState(State::Battle); this->PrintMenuText(); };
			denyAction = [&]() { SetState(State::GameOver); };
		}
	}
}

void FootballGame::UpdateUserInput()
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
		if (keys.at('B'))
		{
			PrintMenuText("Are you sure you want reset ball position? [Y/N]");

			acceptAction = [&]()
			{
				ball = defaultBall;
				ball.current_position.x += rand() % 10 - 5;
				ball.current_position.y += rand() % 10 - 5;
				this->PrintMenuText(); 
			};
			denyAction = [&]() { this->PrintMenuText(); };
		}
		if (keys.at('Q'))
		{
			PrintMenuText("Are you sure you want to increase speed of the game? [Y/N]");

			acceptAction = [&]() { IncreaseGameSpeed(); this->PrintMenuText(); };
			denyAction = [&]() { this->PrintMenuText(); };
		}
		if (keys.at('W'))
		{
			PrintMenuText("Are you sure you want to decrease speed of the game? [Y/N]");

			acceptAction = [&]() { DecreaseGameSpeed(); this->PrintMenuText(); };
			denyAction = [&]() { this->PrintMenuText(); };
		}
		if (keys.at('A'))
		{
			PrintMenuText("Are you sure you want to increase size of goal? [Y/N]");

			acceptAction = [&]()
			{
				if (goalSize < mapHeight / 2 - 1)
				{
					goalSize += 2;
					SetDefaultMapColors();
					ResetMapToDefault();
				}
				this->PrintMenuText();
			};
			denyAction = [&]() { this->PrintMenuText(); };
		}
		if (keys.at('S'))
		{
			PrintMenuText("Are you sure you want to decrease size of goal? [Y/N]");

			acceptAction = [&]()
			{
				if (goalSize > 3)
				{
					goalSize -= 2;
					SetDefaultMapColors();
					ResetMapToDefault();
				}
				this->PrintMenuText();
			};
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

void FootballGame::RestartGame()
{
	score = {};
	goalSize = defaultGoalSize;
	ResetPlayers();
	ball = defaultBall;

	SetDefaultMapColors();
	ResetMapToDefault();
}

void FootballGame::Print()
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

std::map<int, bool>& FootballGame::GetKeyMap()
{
	return keys;
}