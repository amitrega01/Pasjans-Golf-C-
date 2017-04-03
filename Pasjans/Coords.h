#pragma once 
#include <Windows.h>

#include <iostream>
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
void gotoXY(int x, int y) {
	//Initialize the coordinates
	COORD coord = { x, y };
	//Set the position
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	return;
}

void getCursorXY(int &x, int&y) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
		x = csbi.dwCursorPosition.X;
		y = csbi.dwCursorPosition.Y;

	}
}