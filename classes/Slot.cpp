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

void Slot::addAttackedBy(Piece* piece) {
	bool alreadyAttacked = false;
	for (unsigned int i = 0; i < this->attackedByCount; i++) {
		if (this->attackedBy[i] == piece) {
			alreadyAttacked = true;
			break;
		}
	}
	if (!alreadyAttacked) {
		Piece** oldPtr = this->attackedBy;
		this->attackedBy = new Piece * [this->attackedByCount + 1];
		for (unsigned int i = 0; i < this->attackedByCount; i++) {
			this->attackedBy[i] = oldPtr[i];
		}
		this->attackedBy[this->attackedByCount++] = piece;
		delete[] oldPtr;
	}
}

void Slot::removeAttackedBy(Piece* piece) {
	Piece** oldPtr = this->attackedBy;
	this->attackedBy = new Piece * [this->attackedByCount - 1];
	unsigned int j = 0;
	for (unsigned int i = 0; i < this->attackedByCount; i++) {
		if (oldPtr[i] != piece) {
			this->attackedBy[j++] = oldPtr[i];
		}
	}
	this->attackedByCount--;
	delete[] oldPtr;
}

