#pragma once

#ifndef POSSIBLE_MOVE_H
#define POSSIBLE_MOVE_H

#include "../Piece.h"

class PossibleMove : public Piece {
public:
	PossibleMove(
		Piece* piece,
		Coords coord,
		Player& player,
		Board& board
	);
};

#endif