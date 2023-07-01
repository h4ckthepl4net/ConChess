#pragma once

#ifndef QUEEN_H
#define QUEEN_H

#include "../Piece.h"
#include "Bishop.h"
#include "Rook.h"

class Queen : public Bishop, public Rook {
public:
	Queen(
		Color color,
		Player& player,
		Board& board
	);
	std::pair<Coords*, unsigned int> getAvailableMoves() const override;
	bool canMove(Coords coord) const override;
	bool isMoveAlgorithmSatisfied(const Coords& coord) const override;
};

#endif