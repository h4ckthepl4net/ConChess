#include "../../headers/special-pieces/King.h"
#include "../../headers/Board.h"

King::King(
	Color color,
	Player& player,
	Board& board
) : Piece(
	color,
	Pieces::KING,
	PieceIDs::KING,
	PieceSymbols::KING,
	PiecePoints::KING,
	Fields::E1,
	player,
	board
) {
}

std::pair<Coords*, unsigned int> King::getAvailableMoves() const {
	// TODO implement
	return std::pair(nullptr, 0);
}

bool King::canMove(Coords coords) const {
	// TODO implement
	return false;
}

bool King::isMoveAlgorithmSatisfied(const Coords& coords) const {
	// TODO implement
	return false;
}