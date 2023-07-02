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

std::pair<Coords*, unsigned int> Pawn::getAvailableMoves(bool updateAttacksAndBlocks) {
	const Coords& coords = this->coords;
	std::int8_t coef = this->isWhite() ? 1 : -1;
	Coords* availableMoves = new Coords[4];
	int availableMovesCount = 0;
	char forwardPieceX = coords.x;
	char forwardPieceY = coords.y + coef;
	Coords forwardCoords = { forwardPieceY, forwardPieceX };
	bool canMoveForward = this->canMove(forwardCoords);
	if (canMoveForward) {
		availableMoves[availableMovesCount] = forwardCoords;
		availableMovesCount++;
	}
	char doubleForwardPieceX = coords.x;
	char doubleForwardPieceY = coords.y + coef * 2;
	Coords doubleForwardCoords = { doubleForwardPieceY, doubleForwardPieceX };
	if (this->canMove(doubleForwardCoords) && canMoveForward) {
		availableMoves[availableMovesCount] = doubleForwardCoords;
		availableMovesCount++;
	}
	if (coords.x > 0) {
		char leftPieceX = coords.x - 1;
		char leftForwardPieceY = coords.y + coef;
		Coords leftForwardCoords = { leftForwardPieceY, leftPieceX };
		if (this->canMove(leftForwardCoords)) {
			availableMoves[availableMovesCount] = leftForwardCoords;
			availableMovesCount++;
		}
		// TODO maybe blocked needed, not sure
		this->board.addAttackedBy(leftForwardCoords, this);
		this->addAttackedSlot(this->board.slotAt(leftForwardCoords));
	}
	if (coords.x < this->board.getWidth() - 1) {
		char rightPieceX = coords.x + 1;
		char rightForwardPieceY = coords.y + coef;
		Coords rightForwardCoords = { rightForwardPieceY, rightPieceX };
		if (this->canMove(rightForwardCoords)) {
			availableMoves[availableMovesCount] = rightForwardCoords;
			availableMovesCount++;
		}
		// TODO maybe blocked needed, not sure
		this->board.addAttackedBy(rightForwardCoords, this);
		this->addAttackedSlot(this->board.slotAt(rightForwardCoords));
	}
	return std::pair(availableMoves, availableMovesCount);
}

bool Pawn::move(Coords coords) {
	Coords delta = this->getDelta(coords);
	
	Piece* targetCell = this->board.pieceAt({ coords.x, coords.y });
	char besidePieceX = this->coords.x + delta.x;
	char besidePieceY = this->coords.y;
	Piece* besideCell = this->board.pieceAt({ besidePieceX, besidePieceY });

	bool result = Piece::move(coords);
	this->isOpenToEmpassant = abs(delta.y) == 2 && result;

	if (besideCell && !this->isSameColor(besideCell) && abs(delta.x) == 1 && abs(delta.y) == 1 && !targetCell && result) {
		Piece* eatenPiece = this->board.removePiece(besideCell->getCoords());
		this->owner.addEatenPiece(eatenPiece);
	}
	
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
			Pawn* pawnBeside = pieceBeside ? dynamic_cast<Pawn*>(pieceBeside) : nullptr;
			if (pieceBeside && pawnBeside) {
				Pawn* pawnBeside = static_cast<Pawn*>(pieceBeside);
				return pawnBeside->isOpenToEmpassant && pawnBeside->getNoMoveCycles() == 1;
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