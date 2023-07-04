#pragma once

#ifndef ROOK_H
#define ROOK_H

#include "../Piece.h"

class Rook : virtual public Piece {
public:
	Rook(
		Color color,
		Coords initialCoord,
		Player& player,
		Board& board
	);
	std::pair<Coords*, unsigned int> getAvailableMoves(bool = false, bool = true) override;
	bool canMove(Coords coord, bool = true) const override;
	bool isMoveAlgorithmSatisfied(const Coords& coord) const override;
};

#endif