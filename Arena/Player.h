#pragma once

class Game;

class Player
{
	friend class Game;

private:
	virtual void CalculateNextMove();
	virtual void ResetNextMove();

};