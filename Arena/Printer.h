#pragma once

#include <Windows.h>
#include <string>

enum Color
{
	Black,
	Blue,
	Green,
	Aqua,
	Red,
	Purple,
	Yellow,
	White,
	Gray,
	LightBlue,
	LightGreen,
	LightAqua,
	LightRed,
	LightPurple,
	LightYellow,
	BrightWhite,

	BG_Black = 0,
	BG_Blue = 16,
	BG_Green = 32,
	BG_Aqua = 48,
	BG_Red = 64,
	BG_Purple = 80,
	BG_Yellow = 96,
	BG_White = 112,
	BG_Gray = 128,
	BG_LightBlue = 144,
	BG_LightGreen = 160,
	BG_LightAqua = 176,
	BG_LightRed = 192,
	BG_LightPurple = 208,
	BG_LightYellow = 224,
	BG_BrightWhite = 240,
};

class Printer
{
public:
	static void Gotoxy(HANDLE hConsole, int x, int y);
	static void ShowConsoleCursor(HANDLE hConsole, bool showFlag);
	static void ClearBuffer(HANDLE hConsole, int x, int y, int size);

	template<typename ...T>
	static void PrintCenter(HANDLE hConsole, int consoleWidth, int y, const T&... lines)
	{
		auto lineY = y;
		auto PrintLine = [consoleWidth, hConsole, &lineY](const std::string& line)
		{
			DWORD dwBytesWritten = 0;

			int startX = (consoleWidth - line.size()) / 2;

			if (startX < 0)
				startX = 0;

			WriteConsoleOutputCharacterA(hConsole, line.c_str(), (std::min)(static_cast<int>(line.size()), consoleWidth), { static_cast<short>(startX), static_cast<short>(lineY) }, &dwBytesWritten);

			lineY++;
		};

		(PrintLine(lines), ...);
	}
};
