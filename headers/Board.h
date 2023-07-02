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
	std::pair<Coords*, unsigned int> markedPossibleMoves;

	Console& console;

	public:
		Board (Console&, unsigned short = 8, unsigned short = 8);
		void initBoard ();
		void placePieces(Piece**, unsigned char);
		Piece* removePiece(Coords);
		void draw (bool wasMove = false) const;
		Piece* move (Coords, Coords);
		Piece* pieceAt(COORD) const;
		Piece* pieceAt(unsigned short) const;
		Slot* slotAt(Coords) const;
		Slot* slotAt(COORD) const;
		Slot* slotAt(unsigned short) const;
		bool click(COORD);
		bool click(unsigned short);
		bool isPieceSelected();
		short getHeight();
		short getWidth();
		bool isPossibleMove(const Coords&) const;
		bool isPossibleMove(const unsigned short&) const;
		void addAttackedBy(Coords coord, Piece* piece);
		void removeAttackedBy(Coords coord, Piece* piece);

	friend class Console;
};

#endif // !BOARD_H
