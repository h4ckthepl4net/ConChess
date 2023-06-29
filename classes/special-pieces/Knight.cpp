#include "../../headers/special-pieces/Knight.h"

Knight::Knight(
	Color color,
	Coords initialCoord,
	Player& player,
	Board& board
) : Piece(
	color,
	Pieces::KNIGHT,
	PieceIDs::KNIGHT,
	PieceSymbols::KNIGHT,
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