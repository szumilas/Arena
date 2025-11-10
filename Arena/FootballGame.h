#pragma once

#include "Game.h"
#include "Printer.h"

struct Coordinates
{
	Coordinates() {}
	template<typename T1, typename T2>
	Coordinates(const T1& t1, const T2& t2) : x(t1), y(t2) {}

	bool operator<(const Coordinates& c) const
	{
		if (x != c.x) return x < c.x;
		return y < c.y;
	}

	Coordinates operator+(const Coordinates& c) const
	{
		return { x + c.x, y + c.y };
	}

	template<typename T>
	Coordinates operator*(const T& c) const
	{
		return { x * c, y * c };
	}

	template<typename T>
	Coordinates operator/(const T& c) const
	{
		return { x / c, y / c };
	}
	
	double x{};
	double y{};
};

class FootballGame;

struct Object
{
	Object(Coordinates current_position, Coordinates target_position, Coordinates velocity, char item, bool bounces)
		: current_position(current_position), target_position(target_position), velocity(velocity), item(item), bounces(bounces) {}

	Coordinates current_position;
	Coordinates target_position;

private:
	Coordinates velocity;

	char item = 'x';

	bool bounces{};

	friend FootballGame;
};



struct Footballer : Object
{
	Footballer(Coordinates c, char number)
		: Object(c, {}, {}, number, false)
	{

	}
};

class FootballGame : public Game
{
public:
	template<typename ...Args>
	FootballGame(int noOfFootballers, int winningScore, const Args&... args) : Game(args...), noOfFootballers(noOfFootballers), winningScore(winningScore) {}

	void Update();
	void UpdateObjectAndPreparedToPrint(Object& object, int color);
	void UpdateBall(bool ballKicked);

	double CalculateDistance(const Coordinates& p1, const Coordinates& p2) const;
	std::pair<bool, int> CheckGoal();
	void CheckWhoWon();
	void UpdateUserInput();
	void Print();

	inline Object& GetBall() { return ball; }
	inline std::list<std::unique_ptr<Player>>& GetPlayers() { return players; }
	inline char GetMapElement(int x, int y) { return Game::GetMapElement(x, y); }
	inline int GetMapWidth() { return pitchWidth; }
	inline int GetMapHeight() { return pitchHeight; }
	inline std::pair<int, int> GetScore() {return score; }
	inline std::pair<double, double> GetGoalRange() { return { pitchHeight / 2 - goalSize / 2, pitchHeight / 2 + goalSize / 2 }; };
	inline int GetNoOfFootballers() { return noOfFootballers; }

private:
	void SetDefaultMapColors();
	virtual void ResetPlayers();
	virtual void Initialize();
	void InitializeKeysMap();
	void SetDefaultMap();
	bool UpdatePlayersPosition();
	void PrepareToPrint();
	void PrintPanel();
	void PrintStats();
	void PrintIntro();
	void PrintMenuText(std::string menuText = "[P] Pause [R] Restart [E] Exit [B] Reset Ball [Q/W] GameSpeed ++/-- [A/S] GoalSize ++/--");
	std::map<int, bool>& GetKeyMap() final;
	void RestartGame();

private:

	int pitchWidth = mapWidth - 1;
	int pitchHeight = mapHeight - 1;
	int noOfFootballers;
	int winningScore;

	int defaultMapColor = BG_LightGreen | BrightWhite;

	std::map<int, bool> keys;

	std::function<void()> acceptAction = nullptr;
	std::function<void()> denyAction = nullptr;

	Object defaultBall{ {pitchWidth * 0.5, pitchHeight * 0.5}, {}, {}, 'o', true};
	Object ball = defaultBall;

	std::multimap<Coordinates, std::pair<char, int>> previousElementsToPrint;
	std::multimap<Coordinates, std::pair<char, int>> elementsToPrint;

	int awayColor = Color::LightYellow | Color::BG_Green;
	int homeColor = Color::LightYellow | Color::BG_LightPurple;
	int ballColor = Color::BrightWhite | Color::BG_Black;
	int unknownColor = Color::LightPurple | Color::BG_Green;

	int defaultGoalSize = mapHeight / 5;
	int goalSize = defaultGoalSize;

	std::pair<int, int> score{};

	const double frictionCoefficient = 0.98;
};