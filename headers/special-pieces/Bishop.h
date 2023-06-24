#pragma once

#ifndef BISHOP_H
#define BISHOP_H

#include "../Piece.h"

class Bishop : public Piece {
public:
	Bishop(
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