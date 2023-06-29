#pragma once

#ifndef KING_H
#define KING_H

#include "../Piece.h"

class King : public Piece {
public:
	King(
		Color color,
		Player& player,
		Board& board
	);
	Coords* getAvailableMoves() const override;
	bool canMove(Coords coord) const override;
};

#endif