#include "TicTacToePlayerRandom.h"
#include "TurboSnakePlayerRandom.h"

#include <memory>

#include <stdio.h>
#include <string>
#include <windows.h>
#include <chrono>
#include <iostream>

int main()
{
	//TicTacToeGame game(Game::Strategy::TurnBased, 1000);
	//game.AddPlayer<TicTacToePlayerRandom>('x');
	//game.AddPlayer<TicTacToePlayerRandom>('o');x

	/*TurboSnakeGame game(Game::Strategy::RealTime, 50);

	game.AddPlayer<TurboSnakePlayerRandom>();

	game.Start();*/

	std::string str;

	srand(time(NULL));

	for (int q = 0; q < 10000; q++)
		str.push_back(static_cast<char>(rand() % ('Z' - 'A') + 'A'));

	auto t_start_str = std::chrono::high_resolution_clock::now();
	std::cout << str;
	auto t_end_str = std::chrono::high_resolution_clock::now();

	double elapsed_time_ms_str = std::chrono::duration<double, std::milli>(t_end_str - t_start_str).count();

	t_start_str = std::chrono::high_resolution_clock::now();
	printf("%s", str);
	t_end_str = std::chrono::high_resolution_clock::now();

	double elapsed_time_ms_printf = std::chrono::duration<double, std::milli>(t_end_str - t_start_str).count();

}