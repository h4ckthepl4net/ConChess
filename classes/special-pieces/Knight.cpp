#include "../../headers/special-pieces/Knight.h"

Knight::Knight(
	Color color,
	Pieces name,
	PieceIDs id,
	PieceSymbols symbol,
	Coords initialCoord,
	Player& player,
	Board& board
) : Piece(
	color,
	name,
	id,
	symbol,
	initialCoord,
	player,
	board
) {
}

Coords* Knight::getAvailableMoves() const {
	// TODO implement
	return nullptr;
}

bool Knight::canMove(Coords coords) const {
	// TODO implement
	return false;
}