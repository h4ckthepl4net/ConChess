#include "../../headers/special-pieces/Rook.h"


Rook::Rook(
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

Coords* Rook::getAvailableMoves() const {
	// TODO implement
	return nullptr;
}

bool Rook::canMove(Coords coords) const {
	// TODO implement
	return false;
}