#pragma once

#ifndef PAWN_H
#define PAWN_H

#include "../Piece.h"

class Pawn : public Piece {
public:
	Pawn(
		Color color,
		Pieces name,
		PieceIDs id,
		PieceSymbols symbol,
		Coords initialCoord,
		Player& player,
		Board& board
	);
	Coords* getAvailableMoves() const override;
	bool canMove(Coords coord) const override;
};

#endif