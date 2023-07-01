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
	// TODO implement
	return std::pair(nullptr, 0);
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
	if (!this->isMoved && delta.y == 2 && delta.x == 0 || delta.y == 1) {
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