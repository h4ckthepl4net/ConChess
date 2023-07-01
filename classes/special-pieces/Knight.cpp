#include "../../headers/special-pieces/Knight.h"
#include "../../headers/Board.h"

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
	PiecePoints::KNIGHT,
	initialCoord,
	player,
	board
) {
}

std::pair<Coords*, unsigned int> Knight::getAvailableMoves() const {
	// TODO implement
	return std::pair(nullptr, 0);
}

bool Knight::canMove(Coords coords) const {
	if (this->isMoveAlgorithmSatisfied(coords)) {
		Coords delta = this->getDelta(coords);
		Piece* piece = this->board.pieceAt({ coords.x, coords.y });
		if (piece && !this->isSameColor(piece) || !piece) {
			return true;
		}
	}
	return false;
}

bool Knight::isMoveAlgorithmSatisfied(const Coords& coords) const {
	Coords delta = this->getColorBasedDelta(coords);
	return abs(delta.y) == 2 && abs(delta.x) == 1 ||
			abs(delta.y) == 1 && abs(delta.x) == 2;
}