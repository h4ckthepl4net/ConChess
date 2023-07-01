#pragma once

#ifndef ROOK_H
#define ROOK_H

#include "../Piece.h"

class Rook : public Piece {
public:
	Rook(
		Color color,
		Coords initialCoord,
		Player& player,
		Board& board
	);
	std::pair<Coords*, unsigned int> getAvailableMoves() const override;
	bool canMove(Coords coord) const override;
	bool isMoveAlgorithmSatisfied(const Coords& coord) const override;
};

#endif