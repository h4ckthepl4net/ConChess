#include "../../headers/special-pieces/Queen.h"
#include "../../headers/Board.h"

Queen::Queen(
	Color color,
	Player& player,
	Board& board
) :	Bishop(
		color,
		Fields::D1,
		player,
		board
	),
	Rook(
		color,
		Fields::D1,
		player,
		board
	),
	Piece(
		color,
		Pieces::QUEEN,
		PieceIDs::QUEEN,
		PieceSymbols::QUEEN,
		PiecePoints::QUEEN,
		Fields::D1,
		player,
		board
	) {}

std::pair<Coords*, unsigned int> Queen::getAvailableMoves() const {
	// TODO implement
	return std::pair(nullptr, 0);
}

bool Queen::canMove(Coords coords) const {
	if (this->isMoveAlgorithmSatisfied(coords)) {
		Coords delta = this->getDelta(coords);
		Piece* piece = this->board.pieceAt({ coords.x, coords.y });
		if (piece && !this->isSameColor(piece) || !piece) {
			return Bishop::canMove(coords) || Rook::canMove(coords);
		}
	}
	return false;
}

bool Queen::isMoveAlgorithmSatisfied(const Coords& coords) const {
	return Bishop::isMoveAlgorithmSatisfied(coords) || Rook::isMoveAlgorithmSatisfied(coords);
}