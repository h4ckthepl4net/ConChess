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

std::pair<Coords*, unsigned int> Bishop::getAvailableMoves(bool updateAttacksAndBlocks) {
	Coords* availableMoves = new Coords[14];
	unsigned int availableMovesCount = 0;
	const short boardHeight = this->board.getHeight();
	const short boardWidth = this->board.getWidth();
	bool upRight = true;
	Coords upRightCoords;
	bool downRight = true;
	Coords downRightCoords;
	bool upLeft = true;
	Coords upLeftCoords;
	bool downLeft = true;
	Coords downLeftCoords;
	for (char i = 1; i < 8; i++) {
		if (upRight) {
			upRightCoords = { this->coords.y + i, this->coords.x + i };
			if (upRightCoords.x >= 0 && upRightCoords.x < boardWidth &&
				upRightCoords.y >= 0 && upRightCoords.y < boardHeight &&
				this->canMove(upRightCoords)) {
				if (this->considerChecked(upRightCoords)) {
					availableMoves[availableMovesCount++] = upRightCoords;
				}
			} else {
				char previousInd = i - 1;
				char previousY = this->coords.y + previousInd;
				char previousX = this->coords.x + previousInd;
				if (previousX >= 0 && previousX < boardWidth &&
					previousY >= 0 && previousY < boardHeight) {
					Piece* previous = this->board.pieceAt({ previousX, previousY });
					if (previous) {
						upRightCoords.x = previous != this ? previousX : boardWidth;
						upRightCoords.y = previous != this ? previousY : boardHeight;
						upRight = false;
					}
				}
			}
		}
		if (downRight) {
			downRightCoords = { this->coords.y - i, this->coords.x + i };
			if (downRightCoords.x >= 0 && downRightCoords.x < boardWidth &&
				downRightCoords.y >= 0 && downRightCoords.y < boardHeight &&
				this->canMove(downRightCoords)) {
				if (this->considerChecked(downRightCoords)) {
					availableMoves[availableMovesCount++] = downRightCoords;
				}
			}
			else {
				char previousInd = i - 1;
				char previousY = this->coords.y - previousInd;
				char previousX = this->coords.x + previousInd;
				if (previousX >= 0 && previousX < boardWidth &&
					previousY >= 0 && previousY < boardHeight) {
					Piece* previous = this->board.pieceAt({ previousX, previousY });
					if (previous) {
						downRightCoords.x = previous != this ? previousX : boardWidth;
						downRightCoords.y = previous != this ? previousY : -1;
						downRight = false;
					}
				}
			}
		}
		if (downLeft) {
			downLeftCoords = { this->coords.y - i, this->coords.x - i };
			if (downLeftCoords.x >= 0 && downLeftCoords.x < boardWidth &&
				downLeftCoords.y >= 0 && downLeftCoords.y < boardHeight &&
				this->canMove(downLeftCoords)) {
				if (this->considerChecked(downLeftCoords)) {
					availableMoves[availableMovesCount++] = downLeftCoords;
				}
			}
			else {
				char previousInd = i - 1;
				char previousY = this->coords.y - previousInd;
				char previousX = this->coords.x - previousInd;
				if (previousX >= 0 && previousX < boardWidth &&
					previousY >= 0 && previousY < boardHeight) {
					Piece* previous = this->board.pieceAt({ previousX, previousY });
					if (previous) {
						downLeftCoords.x = previous != this ? previousX : -1;
						downLeftCoords.y = previous != this ? previousY : -1;
						downLeft = false;
					}
				}
			}
		}
		if (upLeft) {
			upLeftCoords = { this->coords.y + i, this->coords.x - i };
			if (upLeftCoords.x >= 0 && upLeftCoords.x < boardWidth &&
				upLeftCoords.y >= 0 && upLeftCoords.y < boardHeight &&
				this->canMove(upLeftCoords)) {
				if (this->considerChecked(upLeftCoords)) {
					availableMoves[availableMovesCount++] = upLeftCoords;
				}
			}
			else {
				char previousInd = i - 1;
				char previousY = this->coords.y + previousInd;
				char previousX = this->coords.x - previousInd;
				if (previousX >= 0 && previousX < boardWidth &&
					previousY >= 0 && previousY < boardHeight) {
					Piece* previous = this->board.pieceAt({ previousX, previousY });
					if (previous) {
						upLeftCoords.x = previous != this ? previousX : -1;
						upLeftCoords.y = previous != this ? previousY : boardHeight;
						upLeft = false;
					}
				}
			}
		}
	}
	if (updateAttacksAndBlocks) {
		if (!upRight && upRightCoords.x < boardWidth && upRightCoords.y < boardHeight) {
			Piece* upRightBlockingPiece = this->board.pieceAt({ upRightCoords.x, upRightCoords.y });
			this->board.addAttackedBy(upRightCoords, this);
			this->addAttackedSlot(this->board.slotAt(upRightCoords));
			if (upRightBlockingPiece && this->isSameColor(upRightBlockingPiece)) {
				upRightBlockingPiece->addBlockedPiece(this);
			}
		}
		if (!downRight && downRightCoords.x < boardWidth && downRightCoords.y >= 0) {
			Piece* downRightBlockingPiece = this->board.pieceAt({ downRightCoords.x, downRightCoords.y });
			this->board.addAttackedBy(downRightCoords, this);
			this->addAttackedSlot(this->board.slotAt(downRightCoords));
			if (downRightBlockingPiece && this->isSameColor(downRightBlockingPiece)) {
				downRightBlockingPiece->addBlockedPiece(this);
			}
		}
		if (!upLeft && upLeftCoords.x >= 0 && upLeftCoords.y < boardHeight) {
			Piece* upLeftBlockingPiece = this->board.pieceAt({ upLeftCoords.x, upLeftCoords.y });
			this->board.addAttackedBy(upLeftCoords, this);
			this->addAttackedSlot(this->board.slotAt(upLeftCoords));
			if (upLeftBlockingPiece && this->isSameColor(upLeftBlockingPiece)) {
				upLeftBlockingPiece->addBlockedPiece(this);
			}
		}
		if (!downLeft && downLeftCoords.x >= 0 && downLeftCoords.y >= 0) {
			Piece* downLeftBlockingPiece = this->board.pieceAt({ downLeftCoords.x, downLeftCoords.y });
			this->board.addAttackedBy(downLeftCoords, this);
			this->addAttackedSlot(this->board.slotAt(downLeftCoords));
			if (downLeftBlockingPiece && this->isSameColor(downLeftBlockingPiece)) {
				downLeftBlockingPiece->addBlockedPiece(this);
			}
		}

		for (unsigned int i = 0; i < availableMovesCount; i++) {
			this->board.addAttackedBy(availableMoves[i], this);
			this->addAttackedSlot(this->board.slotAt(availableMoves[i]));
		}
	}

	return std::pair(availableMoves, availableMovesCount);
}

bool Bishop::canMove(Coords coords) const {
	if (this->isMoveAlgorithmSatisfied(coords)) {
		Coords delta = this->getDelta(coords);
		Piece* piece = this->board.pieceAt({ coords.x, coords.y });
		if (piece && !this->isSameColor(piece) || !piece) {
			if (delta.x && delta.y) {
				const char xStart = delta.x < 0 ? coords.x : this->coords.x;
				const char yStart = delta.x < 0 ? coords.y : this->coords.y;
				const char xEnd = delta.x >= 0 ? coords.x : this->coords.x;
				const char yEnd = delta.x >= 0 ? coords.y : this->coords.y;
				std::int8_t yCoef = yEnd < yStart ? -1 : 1;
				for (char i = xStart + 1, j = yStart + yCoef; i < xEnd; i++, j += yCoef) {
					if (this->board.pieceAt({ i, j })) {
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