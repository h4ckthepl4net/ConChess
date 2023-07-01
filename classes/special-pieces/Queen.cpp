#include "../../headers/special-pieces/Queen.h"

Queen::Queen(
	Color color,
	Player& player,
	Board& board
) :	Piece(
	color,
	Pieces::QUEEN,
	PieceIDs::QUEEN,
	PieceSymbols::QUEEN,
	PiecePoints::QUEEN,
	Fields::D1,
	player,
	board
) {
}

std::pair<Coords*, unsigned int> Queen::getAvailableMoves() const {
	// TODO implement
	return std::pair(nullptr, 0);
}

bool Queen::canMove(Coords coords) const {
	// TODO implement
	return false;
}

bool Queen::isMoveAlgorithmSatisfied(const Coords& coords) const {
	// TODO implement
	return false;
}