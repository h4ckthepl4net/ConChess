#include "../../headers/special-pieces/Pawn.h"
#include "../../headers/Board.h"

Pawn::Pawn(
	Color color,
	Coords initialCoord,
	Player& player,
	Board& board
) :	Piece(
	color,
	Pieces::PAWN,
	PieceIDs::PAWN,
	PieceSymbols::PAWN,
	PiecePoints::PAWN,
	initialCoord,
	player,
	board,
	true
) {
}

std::pair<Coords*, unsigned int> Pawn::getAvailableMoves() const {
	const Coords& coords = this->coords;
	std::int8_t coef = this->isWhite() ? 1 : -1;
	Coords* availableMoves = new Coords[4];
	int availableMovesCount = 0;
	char forwardPieceX = coords.x;
	char forwardPieceY = coords.y + coef;
	Piece* forwardPiece = this->board.pieceAt({ forwardPieceX, forwardPieceY });
	if (coords.y + coef >= 0 && coords.y + coef < this->board.getHeight() && !forwardPiece) {
		availableMoves[availableMovesCount] = { coords.y + coef, coords.x };
		availableMovesCount++;
	}
	if (coords.y + coef * 2 >= 0 && coords.y + coef * 2 < this->board.getHeight() && !this->hasMoved()) {
		char doubleForwardPieceX = coords.x;
		char doubleForwardPieceY = coords.y + coef * 2;
		Piece* doubleForwardPiece = this->board.pieceAt({ doubleForwardPieceX, doubleForwardPieceY });
		if (!doubleForwardPiece && !forwardPiece) {
			availableMoves[availableMovesCount] = { coords.y + coef * 2, coords.x };
			availableMovesCount++;
		}
	}
	if (coords.x > 0) {
		char leftPieceX = coords.x - 1;
		char leftForwardPieceY = coords.y + coef;
		Piece* leftForwardPiece = this->board.pieceAt({ leftPieceX, leftForwardPieceY });
		Pawn* leftPiece = static_cast<Pawn*>(this->board.pieceAt({ leftPieceX, coords.y }));
		if (leftForwardPiece && !this->isSameColor(leftForwardPiece) ||
			leftPiece && !this->isSameColor(leftPiece) && leftPiece->isOpenToEmpassant && leftPiece->getNoMoveCycles() == 1) {
			availableMoves[availableMovesCount] = { leftForwardPieceY, leftPieceX };
			availableMovesCount++;
		}
	}
	if (coords.x < this->board.getWidth() - 1) {
		char rightPieceX = coords.x + 1;
		char rightForwardPieceY = coords.y + coef;
		Piece* rightForwardPiece = this->board.pieceAt({ rightPieceX, rightForwardPieceY });
		Pawn* rightPiece = static_cast<Pawn*>(this->board.pieceAt({ rightPieceX, coords.y }));
		if (rightForwardPiece && !this->isSameColor(rightForwardPiece) ||
			rightPiece && !this->isSameColor(rightPiece) && rightPiece->isOpenToEmpassant && rightPiece->getNoMoveCycles() == 1) {
			availableMoves[availableMovesCount] = { rightForwardPieceY, rightPieceX };
			availableMovesCount++;
		}
	}
	return std::pair(availableMoves, availableMovesCount);
}

bool Pawn::move(Coords coords) {
	Coords delta = this->getColorBasedDelta(coords);
	bool result = Piece::move(coords);
	this->isOpenToEmpassant = delta.y == 2 && result;
	return result;
}

bool Pawn::canMove(Coords coords) const {
	if (this->isMoveAlgorithmSatisfied(coords)) {
		Coords delta = this->getDelta(coords);
		Piece* piece = this->board.pieceAt({coords.x, coords.y});
		if (delta.x != 0) {
			if (piece && !this->isSameColor(piece)) {
				return true;
			}
			char besidePieceX = this->coords.x + delta.x;
			char besidePieceY = this->coords.y;
			Piece* pieceBeside = this->board.pieceAt({ besidePieceX, besidePieceY });
			if (pieceBeside && 
				pieceBeside->getId() == pieceIDsToString(PieceIDs::PAWN)) {
				Pawn* pawnBeside = static_cast<Pawn*>(pieceBeside);
				bool canEat = pawnBeside->isOpenToEmpassant && pawnBeside->getNoMoveCycles() == 1;
				if (canEat) {
					Piece* eatenPiece = this->board.removePiece(pawnBeside->getCoords());
					this->owner.addEatenPiece(eatenPiece);
				}
				return canEat;
			}
		}
		else if (!piece) {
			return true;
		}
	}
	return false;
}

bool Pawn::isMoveAlgorithmSatisfied(const Coords& coords) const {
	Coords delta = this->getColorBasedDelta(coords);
	bool isXRangeSatisfied = false;
	bool isYRangeSatisfied = false;
	if (delta.x >= -1 && delta.x <= 1) {
		isXRangeSatisfied = true;
	}
	if (!this->hasMoved() && delta.y == 2 && delta.x == 0 || delta.y == 1) {
		isYRangeSatisfied = true;
	}
	return isXRangeSatisfied && isYRangeSatisfied;
}

void Pawn::incrementNoMoveCycles() {
	Piece::incrementNoMoveCycles();
	if (this->getNoMoveCycles() > 1) {
		this->isOpenToEmpassant = false;
	}
}