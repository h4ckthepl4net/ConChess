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

std::pair<Coords*, unsigned int> Knight::getAvailableMoves(bool updateAttacksAndBlocks) {
	Coords* availableMoves = new Coords[8];
	unsigned int availableMovesCount = 0;
	char boardHeight = static_cast<char>(this->board.getHeight());
	char boardWidth = static_cast<char>(this->board.getWidth());
	for (char i = -1; i <= 1; i+=2) {
		for (char j = -2; j <= 2; j+=4) {
			if (i && j && abs(i) != abs(j)) {
				Coords coords = { this->coords.y + j, this->coords.x + i };
				bool isInBoardArea = coords.x >= 0 && coords.y >= 0 &&
									coords.x < boardWidth && coords.y < boardHeight;
				bool canMove = false;
				if (isInBoardArea) {
					canMove = this->canMove(coords);
					if (canMove) {
						if (this->considerChecked(coords)) {
							availableMoves[availableMovesCount++] = coords;
						}
					} else if (updateAttacksAndBlocks) {
						this->board.addAttackedBy(coords, this);
						this->addAttackedSlot(this->board.slotAt(coords));
						/*Piece* blockingPiece = this->board.pieceAt({ coords.x, coords.y });
						if (blockingPiece) {
							blockingPiece->addBlockedPiece(this);
						}*/
					}
				}
				coords = { this->coords.y + i, this->coords.x + j };
				isInBoardArea = coords.x >= 0 && coords.y >= 0 &&
								coords.x < boardWidth && coords.y < boardHeight;
				if (isInBoardArea) {
					canMove = this->canMove(coords);
					if (canMove) {
						if (this->considerChecked(coords)) {
							availableMoves[availableMovesCount++] = coords;
						}
					} else if (updateAttacksAndBlocks) {
						this->board.addAttackedBy(coords, this);
						this->addAttackedSlot(this->board.slotAt(coords));
						/*Piece* blockingPiece = this->board.pieceAt({ coords.x, coords.y });
						if (blockingPiece) {
							blockingPiece->addBlockedPiece(this);
						}*/
					}
				}
			}
		}
	}
	if (updateAttacksAndBlocks) {
		for (unsigned int i = 0; i < availableMovesCount; i++) {
			this->board.addAttackedBy(availableMoves[i], this);
			this->addAttackedSlot(this->board.slotAt(availableMoves[i]));
		}
	}
	return std::pair(availableMoves, availableMovesCount);
}

bool Knight::canMove(Coords coords) const {
	if (this->isMoveAlgorithmSatisfied(coords)) {
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