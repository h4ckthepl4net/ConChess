#include "../../headers/special-pieces/Knight.h"

Knight::Knight(
	Color color,
	Coords initialCoord,
	Player& player,
	Board& board
) : Piece(
	color,
	Pieces::KNIGHT,
	PieceIDs::KNIGHT,
	PieceSymbols::KNIGHT,
	PiecePoints::KNIGHT,
	initialCoord,
	player,
	board
) {
}

std::pair<Coords*, unsigned int> Knight::getAvailableMoves() const {
	// TODO implement
	return std::pair(nullptr, 0);
}

bool Knight::canMove(Coords coords) const {
	// TODO implement
	return false;
}

bool Knight::isMoveAlgorithmSatisfied(const Coords& coords) const {
	// TODO implement
	return false;
}