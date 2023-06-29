#include "../../headers/special-pieces/Bishop.h"

Bishop::Bishop(
	Color color,
	Coords initialCoord,
	Player& player,
	Board& board
) :	Piece(
	color,
	Pieces::BISHOP,
	PieceIDs::BISHOP,
	PieceSymbols::BISHOP,
	initialCoord,
	player,
	board
) {
}

Coords* Bishop::getAvailableMoves() const {
	// TODO implement
	return nullptr;
}

bool Bishop::canMove(Coords coords) const {
	// TODO implement
	return false;
}