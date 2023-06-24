#include "../../headers/special-pieces/Queen.h"

Queen::Queen(
	Color color,
	Pieces name,
	PieceIDs id,
	PieceSymbols symbol,
	Player& player,
	Board& board
) :	Piece(
	color,
	name,
	id,
	symbol,
	Fields::D1,
	player,
	board
) {
}

Coords* Queen::getAvailableMoves() const {
	// TODO implement
	return nullptr;
}

bool Queen::canMove(Coords coords) const {
	// TODO implement
	return false;
}