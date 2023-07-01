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
	Coords* availableMoves = new Coords[8];
	unsigned int availableMovesCount = 0;
	for (char i = -1; i <= 1; i+=2) {
		for (char j = -2; j <= 2; j+=4) {
			if (i && j && abs(i) != abs(j)) {
				Coords coords = { this->coords.y + j, this->coords.x + i };
				if (coords.x >= 0 && coords.y >= 0 &&
					coords.x < this->board.getWidth() && coords.y < this->board.getHeight() &&
					this->canMove(coords)) {
					availableMoves[availableMovesCount++] = coords;
				}
			}
		}
	}
	for (char i = -1; i <= 1; i += 2) {
		for (char j = -2; j <= 2; j += 4) {
			if (i && j && abs(i) != abs(j)) {
				Coords coords = { this->coords.y + i, this->coords.x + j };
				if (coords.x >= 0 && coords.y >= 0 &&
					coords.x < this->board.getWidth() && coords.y < this->board.getHeight() &&
					this->canMove(coords)) {
					availableMoves[availableMovesCount++] = coords;
				}
			}
		}
	}
	return std::pair(availableMoves, availableMovesCount);
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