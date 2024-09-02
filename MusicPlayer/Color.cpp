#include "Color.h"

Color::Color(){}

Color::Color(HANDLE hStdOut) {
	this->hStdOut = hStdOut;
}

void Color::SetColor(int text, int background) {
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

void Color::ResetColor() {
	SetConsoleTextAttribute(hStdOut, (WORD)((ConsoleColor::Black << 4) | ConsoleColor::White));
}
