#pragma once

#ifndef BOARD_H
#define BOARD_H

#include "Console.h"
#include "Piece.h"

class Board {
	Piece** board = nullptr;
	Piece* pieces = nullptr;
	unsigned short piecesCount = 32;
	unsigned short width;
	unsigned short height;

	Console& console;

	public:
		Board (Console&, unsigned short = 8, unsigned short = 8);
		void initBoard ();
		void placePieces(Piece**, unsigned char);
		void draw () const;
		bool move (Coords, Coords);
};

#endif // !BOARD_H
