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

std::pair<Coords*, unsigned int> Pawn::getAvailableMoves(bool updateAttacksAndBlocks, bool considerKingDefence) {
	const Coords& coords = this->coords;
	if (coords.y > 0 && coords.y < this->board.getHeight() - 1) {
		std::int8_t coef = this->isWhite() ? 1 : -1;
		Coords* availableMoves = new Coords[4];
		int availableMovesCount = 0;
		char forwardPieceX = coords.x;
		char forwardPieceY = coords.y + coef;
		Coords forwardCoords = { forwardPieceY, forwardPieceX };
		bool canMoveForward = this->canMove(forwardCoords, considerKingDefence);
		if (canMoveForward) {
			if (this->considerChecked(forwardCoords)) {
				availableMoves[availableMovesCount] = forwardCoords;
				availableMovesCount++;
			}
		}
		char doubleForwardPieceX = coords.x;
		char doubleForwardPieceY = coords.y + coef * 2;
		Coords doubleForwardCoords = { doubleForwardPieceY, doubleForwardPieceX };
		if (this->canMove(doubleForwardCoords, considerKingDefence) && canMoveForward) {
			if (this->considerChecked(doubleForwardCoords)) {
				availableMoves[availableMovesCount] = doubleForwardCoords;
				availableMovesCount++;
			}
		}
		if (coords.x > 0) {
			char leftPieceX = coords.x - 1;
			char leftForwardPieceY = coords.y + coef;
			Coords leftForwardCoords = { leftForwardPieceY, leftPieceX };
			if (this->canMove(leftForwardCoords, considerKingDefence) && this->considerChecked(leftForwardCoords)) {
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
			if (this->canMove(rightForwardCoords, considerKingDefence) && this->considerChecked(rightForwardCoords)) {
				availableMoves[availableMovesCount] = rightForwardCoords;
				availableMovesCount++;
			}
			// TODO maybe blocked needed, not sure
			this->board.addAttackedBy(rightForwardCoords, this);
			this->addAttackedSlot(this->board.slotAt(rightForwardCoords));
		}
		return std::pair(availableMoves, availableMovesCount);
	}
	return std::pair(nullptr, 0);
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

	if (this->coords.y == 0 || this->coords.y == this->board.getHeight() - 1) {
		this->promote();
	}
	
	return result;
}

bool Pawn::canMove(Coords coords, bool considerKingDefence) const {
	if (this->isMoveAlgorithmSatisfied(coords) &&
		((considerKingDefence && this->considerKingDefense()) || !considerKingDefence)) {
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

void Pawn::promote() {
	ConsoleButton buttons[] = { { 0, "Queen" }, { 1, "Rook" }, { 2, "Bishop" }, { 3, "Knight" } };
	Piece** pieces = new Piece*[4];
	pieces[0] = new Queen(this->color, this->coords, this->owner, this->board);
	pieces[1] = new Rook(this->color, this->coords, this->owner, this->board);
	pieces[2] = new Bishop(this->color, this->coords, this->owner, this->board);
	pieces[3] = new Knight(this->color, this->coords, this->owner, this->board);
	int selectedButtonId = this->board.getConsole().drawPromptAndListen("Promote pawn", buttons, 4);
	Piece* newPiece = pieces[selectedButtonId];
	this->board.removePiece(this->coords); // TODO remove piece from memory
	this->board.placePieces(&newPiece, 1);
	for (unsigned int i = 0; i < 4; i++) {
		if (i != selectedButtonId) {
			delete pieces[i];
		}
	}
	delete[] pieces;
}