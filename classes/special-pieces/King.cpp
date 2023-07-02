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

std::pair<Coords*, unsigned int> King::getAvailableMoves(bool updateAttacksAndBlocks) {
	Coords* availableMoves = new Coords[10];
	unsigned int availableMovesCount = 0;
	for (char i = -1; i < 2; i++) {
		for (char j = -1; j < 2; j++) {
			Coords coords = { this->coords.y + i, this->coords.x + j };
			bool isInBoardArea = coords.x >= 0 && coords.y >= 0 &&
								coords.x < this->board.getWidth() && coords.y < this->board.getHeight();
			if (isInBoardArea) {
				if (this->canMove(coords)) {
					if (this->considerChecked(coords)) {
						availableMoves[availableMovesCount++] = coords;
					}
				}
				else if (updateAttacksAndBlocks) {
					this->board.addAttackedBy(coords, this);
					this->addAttackedSlot(this->board.slotAt(coords));
				}
			}
		}
	}
	if (!this->hasMoved()) {
		Coords castling = { this->coords.y, this->coords.x - 2 };
		if (this->canMove(castling)) {
			if (this->considerChecked(coords)) {
				availableMoves[availableMovesCount++] = castling;
			}
		}
		castling.x = this->coords.x + 2;
		if (this->canMove(castling)) {
			if (this->considerChecked(coords)) {
				availableMoves[availableMovesCount++] = castling;
			}
		}
	}
	return std::pair(availableMoves, availableMovesCount);
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
		if ((piece && !this->isSameColor(piece) || !piece) && !this->board.slotAt(coords)->willBeAttacked(this)) {
			/*if (this->board.isAttacked(coords)) {
				TODO implement checked functionality
			}*/
			if (abs(delta.x) < 2 && abs(delta.y) < 2 && (delta.y || delta.x)) {
				return true;
			} else if (abs(delta.x) == 2 && !this->hasMoved()) {
				char rookX = delta.x > 0 ? 7 : 0;
				Piece* rook = this->board.pieceAt({ rookX, this->coords.y });
				if (!piece && rook && !rook->hasMoved()) {
					Coords preceeding = { this->coords.y, this->coords.x + delta.x / 2 };
					Piece* preceedingPiece = this->board.pieceAt({ preceeding.x, preceeding.y });
					return !preceedingPiece && !this->board.slotAt(preceeding)->willBeAttacked(this);
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