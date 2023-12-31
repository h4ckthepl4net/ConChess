#pragma once

#ifndef SLOT_H
#define SLOT_H

#include "Piece.h"

class Slot {
	Piece* piece = nullptr;
	Piece** attackedBy = nullptr;
	unsigned int attackedByCount = 0;
	Coords coords;

	public:
		bool isPossibleMove = false;
		Slot();
		Slot(Coords);
		Slot(Coords, Piece*);
		Piece* getPiece() const;
		Piece* setPiece(Piece*);
		void setCoords(const Coords&);
		Piece* removePiece();
		bool isEmpty() const;
		void addAttackedBy(Piece*);
		void removeAttackedBy(Piece*);
		bool isAttacked() const;
		bool willBeAttacked(const Piece*) const;
		bool moveWillCoverAllAttacks(const Coords&) const;
		Coords getDelta(const Coords&) const;
		void recalculateAttacks();
		std::pair<Piece**, unsigned int> getAttackedBy() const;
};


#endif