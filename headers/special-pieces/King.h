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
	std::pair<Coords*, unsigned int> getAvailableMoves(bool = false, bool = true) override;
	bool move(Coords) override;
	bool canMove(Coords coord, bool = true) const override;
	bool isMoveAlgorithmSatisfied(const Coords& coord) const override;
	bool considerChecked(const Coords&) const override;
};

#endif