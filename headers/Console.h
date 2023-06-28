#pragma once

#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>
#include <windows.h>

char letterNotation(std::uint8_t num);
class Board;

class Console {
	Board& board;
	HANDLE hConsole;
	CONSOLE_SCREEN_BUFFER_INFOEX consoleInfo;
	unsigned short height;
	unsigned short width;

	void drawBlackTile(std::string = " ", int = 0) const;
	void drawWhiteTile(std::string = " ", int = 0) const;
	void drawBlackTile(char = ' ', int = 0) const;
	void drawWhiteTile(char = ' ', int = 0) const;

	void notateHorizontalFrame(std::uint8_t = 0) const;
	void notateSideFrame(std::uint8_t = 0) const;
public:
	Console(
		Board&,
		unsigned short = 17,
		unsigned short = 17,
		HANDLE = nullptr,
		CONSOLE_SCREEN_BUFFER_INFOEX = {}
	);
	void drawBoard() const;
	void clear() const;
};


#endif // !CONSOLE_H

