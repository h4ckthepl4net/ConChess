#include "../../headers/special-pieces/Pawn.h"

Pawn::Pawn(
	Color color,
	Coords initialCoord,
	Player& player,
	Board& board
) :	Piece(
	color,
	Pieces::PAWN,
	PieceIDs::PAWN,
	PieceSymbols::PAWN,
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