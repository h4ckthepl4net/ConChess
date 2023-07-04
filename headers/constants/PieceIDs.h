#pragma once

#ifndef PIECEIDS_H
#define PIECEIDS_H

#include <stdexcept>

enum class PieceIDs {
	KING,
	QUEEN,
	ROOK,
	BISHOP,
	KNIGHT,
	PAWN,
};

constexpr const char* pieceIDsToString(PieceIDs id) {
	switch (id) {
		case PieceIDs::KING: return "K";
		case PieceIDs::QUEEN: return "Q";
		case PieceIDs::ROOK: return "R";
		case PieceIDs::BISHOP: return "B";
		case PieceIDs::KNIGHT: return "N";
		case PieceIDs::PAWN: return "P";
		default: throw std::invalid_argument("Invalid PieceIDs");
	}
}

#endif