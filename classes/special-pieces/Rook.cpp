#include "../../headers/special-pieces/Rook.h"
#include "../../headers/Board.h"


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
	PiecePoints::ROOK,
	initialCoord,
	player,
	board
) {
}

std::pair<Coords*, unsigned int> Rook::getAvailableMoves() const {
	// TODO implement
	return std::pair(nullptr, 0);
}

bool Rook::canMove(Coords coords) const {
	if (this->isMoveAlgorithmSatisfied(coords)) {
		Coords delta = this->getDelta(coords);
		Piece* piece = this->board.pieceAt({ coords.x, coords.y });
		if (piece && !this->isSameColor(piece) || !piece) {
			if (delta.x) {
				const char start = delta.x < 0 ? coords.x : this->coords.x;
				const char end = delta.x >= 0 ? coords.x : this->coords.x;
				for (char i = start + 1; i < end; i++) {
					if (this->board.pieceAt({ i, this->coords.y })) {
						return false;
					}
				}
			} else if (delta.y) {
				const char start = delta.y < 0 ? coords.y : this->coords.y;
				const char end = delta.y >= 0 ? coords.y : this->coords.y;
				for (char i = start + 1; i < end; i++) {
					if (this->board.pieceAt({ this->coords.x, i })) {
						return false;
					}
				}
			}
			
			return true;
		}
	}
	return false;
}

bool Rook::isMoveAlgorithmSatisfied(const Coords& coords) const {
	Coords delta = this->getColorBasedDelta(coords);
	if (delta.x == 0 && delta.y != 0 || delta.y == 0 && delta.x != 0) {
		return true;
	}
	return false;
}