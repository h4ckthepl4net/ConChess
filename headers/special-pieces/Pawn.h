#pragma once

#ifndef PAWN_H
#define PAWN_H

#include "../Piece.h"

class Pawn : public Piece {
	bool isOpenToEmpassant = false;
public:
	Pawn(
		Color color,
		Coords initialCoord,
		Player& player,
		Board& board
	);
	std::pair<Coords*, unsigned int> getAvailableMoves(bool = false, bool = true) override;
	bool move(Coords) override;
	bool canMove(Coords, bool = true) const override;
	bool isMoveAlgorithmSatisfied(const Coords&) const override;
	void incrementNoMoveCycles() override;
	void promote();
};

#endif