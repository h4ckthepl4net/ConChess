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
	std::pair<Coords*, unsigned int> getAvailableMoves(bool = false) override;
	bool canMove(Coords coord) const override;
	bool isMoveAlgorithmSatisfied(const Coords& coord) const override;
};

#endif