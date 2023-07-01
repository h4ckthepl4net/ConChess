#pragma once

#ifndef BOARD_H
#define BOARD_H

#include "Console.h"
#include "Piece.h"
#include "Slot.h"

class Board {
	Slot* board = nullptr;
	Piece* pieces = nullptr;
	unsigned short piecesCount = 32;
	Piece* selectedPiece = nullptr;
	unsigned short width;
	unsigned short height;

	Console& console;

	public:
		Board (Console&, unsigned short = 8, unsigned short = 8);
		void initBoard ();
		void placePieces(Piece**, unsigned char);
		Piece* removePiece(Coords);
		void draw (bool wasMove = false) const;
		bool move (Coords, Coords);
		Piece* pieceAt(COORD) const;
		Piece* pieceAt(unsigned short) const;
		bool click(COORD);
		bool click(unsigned short);
		bool isPieceSelected();
		short getHeight();
		short getWidth();

	friend class Console;
};

#endif // !BOARD_H
