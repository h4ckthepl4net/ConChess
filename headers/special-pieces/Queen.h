#pragma once

#ifndef QUEEN_H
#define QUEEN_H

#include "../Piece.h"

class Queen : public Piece {
public:
	Queen(
		Color color,
		Player& player,
		Board& board
	);
	Coords* getAvailableMoves() const override;
	bool canMove(Coords coord) const override;
};

#endif