#include "../../headers/special-pieces/Bishop.h"
#include "../../headers/Board.h"

Bishop::Bishop(
	Color color,
	Coords initialCoord,
	Player& player,
	Board& board
) :	Piece(
	color,
	Pieces::BISHOP,
	PieceIDs::BISHOP,
	PieceSymbols::BISHOP,
	PiecePoints::BISHOP,
	initialCoord,
	player,
	board
) {
}

std::pair<Coords*, unsigned int> Bishop::getAvailableMoves() const {
	// TODO implement
	return std::pair(nullptr, 0);
}

bool Bishop::canMove(Coords coords) const {
	// TODO implement
	return false;
}

bool Bishop::isMoveAlgorithmSatisfied(const Coords& coords) const {
	// TODO implement
	return false;
}