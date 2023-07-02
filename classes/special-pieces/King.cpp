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

bool King::move(Coords coords) {
	Coords delta = this->getDelta(coords);
	bool result = Piece::move(coords);
	if (abs(delta.x) == 2 && result) {
		char rookX = delta.x > 0 ? 7 : 0;
		Piece* rook = this->board.removePiece({ this->coords.y, rookX });
		char newRoolX = delta.x > 0 ? 5 : 3;
		rook->setCoords({ this->coords.y, newRoolX });
		this->board.placePieces(&rook, 1);
	};
	return result;
}

bool King::canMove(Coords coords) const {
	if (this->isMoveAlgorithmSatisfied(coords)) {
		Coords delta = this->getDelta(coords);
		Piece* piece = this->board.pieceAt({ coords.x, coords.y });
		if (piece && !this->isSameColor(piece) || !piece) {
			/*if (this->board.isAttacked(coords)) {
				TODO implement checked functionality also moving is not allowed if the field is attacked
			}*/
			if (abs(delta.x) < 2 && abs(delta.y) < 2 && (delta.y || delta.x)) {
				return true;
			} else if (abs(delta.x) == 2 && !this->hasMoved()) {
				char rookX = delta.x > 0 ? 7 : 0;
				Piece* rook = this->board.pieceAt({ rookX, this->coords.y });
				if (rook && !rook->hasMoved()) {
					return true;
				}
			}
		}
	}
	return false;
}

bool King::isMoveAlgorithmSatisfied(const Coords& coords) const {
	Coords delta = this->getDelta(coords);
	return (abs(delta.x) < 2 && abs(delta.y) < 2 && (delta.y || delta.x)) ||
			(abs(delta.x) == 2 && !this->hasMoved());
}