#pragma once

#ifndef SLOT_H
#define SLOT_H

#include "Piece.h"

class Slot {
	Piece* piece = nullptr;
	Piece** attackedBy = nullptr;
	Coords coords;

	public:
		bool isPossibleMove = false;
		Slot();
		Slot(Coords);
		Slot(Coords, Piece*);
		Piece* getPiece() const;
		void setPiece(Piece*);
		void setCoords(const Coords&);
		Piece* removePiece();
		bool isEmpty() const;
};


#endif