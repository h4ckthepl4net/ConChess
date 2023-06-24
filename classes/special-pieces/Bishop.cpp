#include "../../headers/special-pieces/Bishop.h"

Bishop::Bishop(
	Color color,
	Pieces name,
	PieceIDs id,
	PieceSymbols symbol,
	Coords initialCoord,
	Player& player,
	Board& board
) :	Piece(
	color,
	name,
	id,
	symbol,
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