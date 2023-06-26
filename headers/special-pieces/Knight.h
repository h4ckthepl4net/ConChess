#pragma once

#ifndef KNIGHT_H
#define KNIGHT_H

#include "../Piece.h"

class Knight : public Piece {
public:
	Knight(
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