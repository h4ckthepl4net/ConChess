#include "../../headers/special-pieces/Pawn.h"

Pawn::Pawn(
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
	board,
	true
) {
}

Coords* Pawn::getAvailableMoves() const {
	// TODO implement
	return nullptr;
}

bool Pawn::canMove(Coords coords) const {
	// TODO implement
	return false;
}