#pragma once

#ifndef KNIGHT_H
#define KNIGHT_H

#include "../Piece.h"

class Knight : public Piece {
public:
	Knight(
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