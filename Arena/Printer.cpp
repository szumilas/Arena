#include <vector>

#include "Printer.h"

void Printer::Gotoxy(HANDLE hConsole, int x, int y)
{
	COORD coord = { static_cast<short>(x), static_cast<short>(y) };
	SetConsoleCursorPosition(hConsole, coord);
}

void Printer::ShowConsoleCursor(HANDLE hConsole, bool showFlag)
{
	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void Printer::ClearBuffer(HANDLE hConsole, int x, int y, int size)
{
	DWORD dwBytesWritten = 0;

	WriteConsoleOutputAttribute(hConsole, &std::vector<WORD>(size, Color::BG_Black | Color::BrightWhite).front(), size, {static_cast<short>(x), static_cast<short>(y)}, &dwBytesWritten);
	WriteConsoleOutputCharacterA(hConsole, &std::vector<char>(size, ' ').front(), size, { static_cast<short>(x), static_cast<short>(y) }, &dwBytesWritten);
}