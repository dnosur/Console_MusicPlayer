#pragma once
#include <Windows.h>

class Color
{
	 HANDLE hStdOut;
public:
	Color();
	Color(HANDLE hStdOut);

	const enum ConsoleColor
	{
		Black = 0,
		Blue = 1,
		Green = 2,
		Cyan = 3,
		Red = 4,
		Magenta = 5,
		Brown = 6,
		LightGray = 7,
		DarkGray = 8,
		LightBlue = 9,
		LightGreen = 10,
		LightCyan = 11,
		LightRed = 12,
		LightMagenta = 13,
		Yellow = 14,
		White = 15
	};

	void SetColor(int text, int background = ConsoleColor::Black);
	void ResetColor();
};

