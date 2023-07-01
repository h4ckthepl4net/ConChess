#pragma once

#ifndef PIECE_SYMBOLS_H
#define PIECE_SYMBOLS_H

#include <stdexcept>

enum class PieceSymbols {
	KING,
	QUEEN,
	ROOK,
	BISHOP,
	KNIGHT,
	PAWN,
	POSSIBLE_MOVE,
};

constexpr const char* pieceSymbolToString(PieceSymbols symbol) {
	switch (symbol) {
		case PieceSymbols::KING: return "K";
		case PieceSymbols::QUEEN: return "Q";
		case PieceSymbols::ROOK: return "R";
		case PieceSymbols::BISHOP: return "B";
		case PieceSymbols::KNIGHT: return "N";
		case PieceSymbols::PAWN: return "P";
		case PieceSymbols::POSSIBLE_MOVE: return " ";
		default: throw std::invalid_argument("Invalid PieceSymbols");
	}
}

#endif