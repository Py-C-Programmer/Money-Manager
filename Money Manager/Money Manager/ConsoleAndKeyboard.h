#pragma once

#include <consoleapi2.h> //for SetCursPos
#include <processenv.h> //for SetCursPos
#include <WinBase.h> //for SetCursPos
#include <conio.h>
#include <windows.h> 

enum ConsoleColor {
	// Standard text colors
	GRAY = 8, BLUE, GREEN,
	TEAL, RED, PINK,
	YELLOW, WHITE,
	// Faded text colors
	BLACK = 0, BLUE_FADE, GREEN_FADE,
	TEAL_FADE, RED_FADE, PINK_FADE,
	YELLOW_FADE, WHITE_FADE,
	NONE
};

// Set console colors
void SetColor(ConsoleColor text, ConsoleColor background = BLACK)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (short)text | ((short)background << 4));
}

enum Keys {
	Q = 113, W = 119, E = 101, R = 114, T = 116, Y = 121, U = 117, I = 105, O = 111, P = 112,
	ZERO = 48, ONE = 49, TWO = 50, THREE = 51, FOUR = 52, FIVE = 53, SIX = 54, SEVEN = 55, EIGHT = 56, NINE = 57,
	UP_ARROW = 72, DOWN_ARROW = 80, RIGHT_ARROW = 77, LEFT_ARROW = 75,
	ENTER = 13, ESC = 27, DEL = 83, PLUS = 43
};

// Set cursor position
void SetCursPos(short x, short y) //#include <Windows.h>
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


