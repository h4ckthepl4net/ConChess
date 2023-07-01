#pragma once

#ifndef PIECE_POINTS_H
#define PIECE_POINTS_H

#include "../utilities/Coords.h"

namespace PiecePoints {
	// Piece points according to game
	const int KNIGHT = 3;
	const int BISHOP = 3;
	const int ROOK = 5;
	const int QUEEN = 9;
	const int KING = 1000;
	const int PAWN = 1;
}

#endif // !PIECE_POINTS_H