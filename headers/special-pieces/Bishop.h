#pragma once

#ifndef BISHOP_H
#define BISHOP_H

#include "../Piece.h"

class Bishop : virtual public Piece {
public:
	Bishop(
		Color color,
		Coords initialCoord,
		Player& player,
		Board& board
	);
	std::pair<Coords*, unsigned int> getAvailableMoves(bool = false, bool = true) override;
	bool canMove(Coords, bool = true) const override;
	bool isMoveAlgorithmSatisfied(const Coords& coord) const override;
};

#endif