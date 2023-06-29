#include "../../headers/special-pieces/Queen.h"

Queen::Queen(
	Color color,
	Player& player,
	Board& board
) :	Piece(
	color,
	Pieces::QUEEN,
	PieceIDs::QUEEN,
	PieceSymbols::QUEEN,
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