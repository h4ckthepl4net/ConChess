#include "../headers/Slot.h"

Slot::Slot() : coords({ 0, 0 }) {}

Slot::Slot(
	Coords coords
) : coords(coords) {}

Slot::Slot(
	Coords coords,
	Piece* piece
) : coords(coords), piece(piece) {}

void Slot::setCoords(const Coords& coords) {
	this->coords = coords;
}

Piece* Slot::removePiece() {
	Piece* piece = this->piece;
	this->piece = nullptr;
	return piece;
}

bool Slot::isEmpty() const {
	return !this->piece;
}

Piece* Slot::setPiece(Piece* piece) {
	Piece* oldPiece = this->piece;
	this->piece = piece;
	return oldPiece;
}

Piece* Slot::getPiece() const {
	return this->piece;
}

