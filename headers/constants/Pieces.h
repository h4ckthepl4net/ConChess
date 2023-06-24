#pragma once

#ifndef PIECES_H
#define PIECES_H

#include <stdexcept>

enum class Pieces {
	KING,
	QUEEN,
	ROOK,
	BISHOP,
	KNIGHT,
	PAWN,
};

constexpr const char* PiecesToString(Pieces piece) {
	switch (piece) {
		case Pieces::KING: return "King";
		case Pieces::QUEEN: return "Queen";
		case Pieces::ROOK: return "Rook";
		case Pieces::BISHOP: return "Bishop";
		case Pieces::KNIGHT: return "Knight";
		case Pieces::PAWN: return "Pawn";
		default: throw std::invalid_argument("Invalid Pieces");
	}
}

#endif // !PIECES_H