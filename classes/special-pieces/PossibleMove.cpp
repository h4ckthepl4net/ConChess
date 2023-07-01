#include "../../headers/special-pieces/PossibleMove.h"

PossibleMove::PossibleMove(
	Piece* piece
) : Piece(
	Color::UNKNOWN,
	Pieces::POSSIBLE_MOVE,
	PieceIDs::POSSIBLE_MOVE,
	PieceSymbols::POSSIBLE_MOVE,
	piece->getCoords(),
	piece->getOwner(),
	piece->getBoard()
), internalPiece(piece) {}

int PossibleMove::getConsoleColor() {
	return BACKGROUND_GREEN | this->internalPiece->getConsoleColor();
};

std::string PossibleMove::getSymbol() {
	return this->internalPiece->getSymbol();
};

Coords* PossibleMove::getAvailableMoves() const {
	return nullptr;
};

bool PossibleMove::canMove(Coords coords) const {
	return false;
};

Piece* PossibleMove::getInternalPiece() const {
	return this->internalPiece;
};