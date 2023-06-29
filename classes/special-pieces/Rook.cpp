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