#include "../../headers/special-pieces/Rook.h"


Rook::Rook(
	Color color,
	Coords initialCoord,
	Player& player,
	Board& board
) :	Piece(
	color,
	Pieces::ROOK,
	PieceIDs::ROOK,
	PieceSymbols::ROOK,
	PiecePoints::ROOK,
	initialCoord,
	player,
	board
) {
}

std::pair<Coords*, unsigned int> Rook::getAvailableMoves() const {
	// TODO implement
	return std::pair(nullptr, 0);
}

bool Rook::canMove(Coords coords) const {
	// TODO implement
	return false;
}

bool Rook::isMoveAlgorithmSatisfied(const Coords& coords) const {
	// TODO implement
	return false;
}