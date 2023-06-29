#include "../../headers/special-pieces/King.h"

King::King(
	Color color,
	Player& player,
	Board& board
) : Piece(
	color,
	Pieces::KING,
	PieceIDs::KING,
	PieceSymbols::KING,
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