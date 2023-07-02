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

std::pair<Coords*, unsigned int> Rook::getAvailableMoves(bool updateAttacksAndBlocks) {
	Coords* availableMoves = new Coords[14];
	unsigned int availableMovesCount = 0;
	char blockedFromLeft = -1;
	char blockedFromRight = static_cast<char>(this->board.getWidth());
	char blockedFromBottom = -1;
	char blockedFromTop = static_cast<char>(this->board.getHeight());
	for (char i = 0; i < 8; i++) {
		if (i != this->coords.x && blockedFromRight == this->board.getWidth()) {
			if (this->canMove({ this->coords.y, i })) {
				availableMoves[availableMovesCount++] = { this->coords.y, i };
			} else if (updateAttacksAndBlocks) {
				if (i < this->coords.x) {
					blockedFromLeft = i;
				}
				else if (blockedFromRight > i) {
					blockedFromRight = i;
				}
			}
		}
		if (i != this->coords.y && blockedFromTop == this->board.getHeight()) {
			if (this->canMove({ i, this->coords.x })) {
				availableMoves[availableMovesCount++] = { i, this->coords.x };
			} else if (updateAttacksAndBlocks) {
				if (i < this->coords.y) {
					blockedFromBottom = i;
				}
				else if (blockedFromTop > i) {
					blockedFromTop = i;
				}
			}
		}
	}
	if (updateAttacksAndBlocks) {
		if (blockedFromBottom > -1) {
			Piece* bottomBlockingPiece = this->board.pieceAt({ this->coords.x, blockedFromBottom });
			Coords attackedSlotCoords = bottomBlockingPiece->getCoords();
			this->board.addAttackedBy(attackedSlotCoords, this);
			this->addAttackedSlot(this->board.slotAt(attackedSlotCoords));
			if (bottomBlockingPiece && this->isSameColor(bottomBlockingPiece)) {
				bottomBlockingPiece->addBlockedPiece(this);
			}
		}
		if (blockedFromTop < this->board.getHeight()) {
			Piece* topBlockingPiece = this->board.pieceAt({ this->coords.x, blockedFromTop });
			Coords attackedSlotCoords = topBlockingPiece->getCoords();
			this->board.addAttackedBy(attackedSlotCoords, this);
			this->addAttackedSlot(this->board.slotAt(attackedSlotCoords));
			if (topBlockingPiece && this->isSameColor(topBlockingPiece)) {
				topBlockingPiece->addBlockedPiece(this);
			}
		}
		if (blockedFromLeft > -1) {
			Piece* leftBlockingPiece = this->board.pieceAt({ blockedFromLeft, this->coords.y });
			Coords attackedSlotCoords = leftBlockingPiece->getCoords();
			this->board.addAttackedBy(attackedSlotCoords, this);
			this->addAttackedSlot(this->board.slotAt(attackedSlotCoords));
			if (leftBlockingPiece && this->isSameColor(leftBlockingPiece)) {
				leftBlockingPiece->addBlockedPiece(this);
			}
		}
		if (blockedFromRight < this->board.getWidth()) {
			Piece* rightBlockingPiece = this->board.pieceAt({ blockedFromRight, this->coords.y });
			Coords attackedSlotCoords = rightBlockingPiece->getCoords();
			this->board.addAttackedBy(attackedSlotCoords, this);
			this->addAttackedSlot(this->board.slotAt(attackedSlotCoords));
			if (rightBlockingPiece && this->isSameColor(rightBlockingPiece)) {
				rightBlockingPiece->addBlockedPiece(this);
			}
		}

		for (unsigned int i = 0; i < availableMovesCount; i++) {
			this->board.addAttackedBy(availableMoves[i], this);
			this->addAttackedSlot(this->board.slotAt(availableMoves[i]));
		}
	}
	return std::pair(availableMoves, availableMovesCount);
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
	return delta.x == 0 && delta.y != 0 || delta.y == 0 && delta.x != 0;
}