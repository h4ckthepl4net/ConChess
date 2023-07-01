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
	if (this->isMoveAlgorithmSatisfied(coords)) {
		Coords delta = this->getDelta(coords);
		Piece* piece = this->board.pieceAt({ coords.x, coords.y });
		if (piece && !this->isSameColor(piece) || !piece) {
			if (delta.x && delta.y) {
				const char xStart = delta.x < 0 ? coords.x : this->coords.x;
				const char xEnd = delta.x >= 0 ? coords.x : this->coords.x;
				const char yStart = delta.y >= 0 ? coords.y : this->coords.y;
				const char yEnd = delta.y < 0 ? coords.y : this->coords.y;
				for (char i = xStart + 1, j = yStart + 1; i < xEnd && j < yEnd; i++, j++) {
					Piece* p = this->board.pieceAt({ i, j });
					if (p) {
						return false;
					}
				}
				return true;
			}
		}
	}
	return false;
}

bool Bishop::isMoveAlgorithmSatisfied(const Coords& coords) const {
	Coords delta = this->getDelta(coords);
	return abs(delta.x) == abs(delta.y);
}