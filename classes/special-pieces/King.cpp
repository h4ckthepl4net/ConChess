#include "../../headers/special-pieces/King.h"

King::King(
	Color color,
	Pieces name,
	PieceIDs id,
	PieceSymbols symbol,
	Player& player,
	Board& board
) : Piece(
	color,
	name,
	id,
	symbol,
	Fields::E1,
	player,
	board
) {
}

Coords* King::getAvailableMoves() const {
	// TODO implement
	return nullptr;
}

bool King::canMove(Coords coords) const {
	// TODO implement
	return false;
}