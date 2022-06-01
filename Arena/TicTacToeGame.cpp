#include "TicTacToeGame.h"
#include "TicTacToePlayer.h"

#include "Printer.h"

#include <iostream>

void TicTacToeGame::Initialize()
{
	Printer::ShowConsoleCursor(false);

	for (auto& player : players)
	{
		dynamic_cast<TicTacToePlayer*>(player.get())->Initialize(this);
	}
}

void TicTacToeGame::MakeMove(const TicTacToeOutput& move, char sign)
{
	if (board[move.first][move.second] == ' ')
	{
		board[move.first][move.second] = sign;
	}
}

void TicTacToeGame::Print()
{
	Printer::Gotoxy(0, 0);
	std::cout << "   \n   \n   ";
	Printer::Gotoxy(0, 0);

	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			std::cout << board[x][y];
		}
		std::cout << std::endl;
	}


	////Get a console handle
	//HWND myconsole = GetConsoleWindow();
	////Get a handle to device context
	//HDC mydc = GetDC(myconsole);




	//int pixel = 0;




	////Choose any color
	//COLORREF COLOR = RGB(255, 255, 255);




	////Draw pixels
	//for (double i = 0; i < 3.14 * 4; i += 0.05)
	//{
	//	SetPixel(mydc, pixel, (int)(50 + 25 * cos(i)), COLOR);
	//	pixel += 1;
	//}




	//ReleaseDC(myconsole, mydc);
}

Game::State TicTacToeGame::GetState()
{
	auto board = GetBoard();

	auto checkWin = [board](int x1, int y1, int x2, int y2, int x3, int y3)
	{
		return (*board)[x1][y1] != ' ' && (*board)[x1][y1] == (*board)[x2][y2] && (*board)[x1][y1] == (*board)[x3][y3];
	};

	if(checkWin(0,0 , 0,1 , 0,2) || checkWin(1,0 , 1,1 , 1,2) || checkWin(2,0 , 2,1 , 2,2) ||
	   checkWin(0,0 , 1,0 , 2,0) || checkWin(0,1 , 1,1 , 2,1) || checkWin(0,2 , 1,2 , 2,2) ||
	   checkWin(0,0 , 1,1 , 2,2) || checkWin(0,2 , 1,1 , 2,0))
	{
		return Game::State::GameOver;
	}

	return Game::State::Battle;
}