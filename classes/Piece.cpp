#include "../headers/Piece.h"
#include "../headers/Board.h"

Piece::Piece(
	Color color,
	Pieces name,
	PieceIDs id,
	PieceSymbols symbol,
	int points,
	Coords initialCoords,
	Player& player,
	Board& board,
	bool isSecondLine
) :
	color(color),
	name(piecesToString(name)),
	id(pieceIDsToString(id)),
	symbol(pieceSymbolToString(symbol)),
	points(points),
	coords(initialCoords),
	owner(player),
	board(board) {
	if (this->isBlack()) {
		if (isSecondLine) {
			this->addDelta(FieldDeltas::SecondLine);
		}
		else {
			this->addDelta(FieldDeltas::FirstLine);
		}
	}
}

std::string Piece::getId() {
	return this->id;
}

std::string Piece::getSymbol() {
	return this->symbol;
}

Coords Piece::getCoords() {
	return this->coords;
}

bool Piece::isWhite() const {
	return this->color == Color::WHITE;
}

bool Piece::isBlack() const {
	return this->color == Color::BLACK;
}

bool Piece::isUnknown() const {
	return this->color == Color::UNKNOWN;
}

int Piece::getConsoleColor() {
	if (this->isBlack()) {
		return 0;
	}

	return FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
}

Coords Piece::addDelta(Coords delta) {
	short boardHeight = this->board.getHeight();
	this->coords.x += delta.x;
	this->coords.y += delta.y;
	this->coords.y = (boardHeight + this->coords.y) % boardHeight;
	return this->coords;
}

bool Piece::move(Coords coords) {
	if (this->canMove(coords)) {
		Piece* eatenPiece = this->board.move(this->coords, coords);
		this->coords = coords;
		this->isMoved = true;
		this->cyclesStandingWithoutAMove = 0;
		if (eatenPiece) {
			this->owner.addEatenPiece(eatenPiece);
		}
		return true;
	}
	return false;
}

bool Piece::isOwnedBy(const Player* player) {
	return player == &this->owner;
}

Player& Piece::getOwner() {
	return this->owner;
}

Board& Piece::getBoard() {
	return this->board;
}

bool Piece::hasMoved() const {
	return this->isMoved;
}

void Piece::incrementNoMoveCycles() {
	this->cyclesStandingWithoutAMove++;
}

void Piece::incrementCycles() {
	this->cyclesFromGameStart++;
}

int Piece::getNoMoveCycles() {
	return this->cyclesStandingWithoutAMove;
}

int Piece::getCycles() {
	return this->cyclesFromGameStart;
}

Coords Piece::getDelta(const Coords& coords) const {
	return {
		coords.y - this->coords.y,
		coords.x - this->coords.x
	};
}

Coords Piece::getColorBasedDelta(const Coords& coords) const {
	const std::int8_t coef = this->isBlack() ? -1 : 1;
	return {
		coef * (coords.y - this->coords.y),
		coords.x - this->coords.x
	};
}

bool Piece::isSameColor(Piece* piece) const {
	return this->color == piece->color;
}

int Piece::getPoints() {
	return this->points;
}

void Piece::setCoords(Coords coords) {
	this->isMoved = true;
	this->cyclesStandingWithoutAMove = 0;
	this->coords = coords;
}


void Piece::addAttackedSlot(Slot* slot) {
	bool isAlreadyAttacked = false;
	for (unsigned int i = 0; i < this->attackedSlotsCount; i++) {
		if (this->attackedSlots[i] == slot) {
			isAlreadyAttacked = true;
			break;
		}
	}
	if (!isAlreadyAttacked) {
		Slot** oldPtr = this->attackedSlots;
		this->attackedSlots = new Slot * [this->attackedSlotsCount + 1];
		for (unsigned int i = 0; i < this->attackedSlotsCount; i++) {
			this->attackedSlots[i] = oldPtr[i];
		}
		this->attackedSlots[this->attackedSlotsCount++] = slot;
		delete[] oldPtr;
	}
}

void Piece::removeAttackedSlot(Slot* slot) {
	Slot** oldPtr = this->attackedSlots;
	this->attackedSlots = new Slot * [this->attackedSlotsCount - 1];
	unsigned int j = 0;
	for (unsigned int i = 0; i < this->attackedSlotsCount; i++) {
		if (oldPtr[i] != slot) {
			this->attackedSlots[j++] = oldPtr[i];
		}
	}
	this->attackedSlotsCount--;
	delete[] oldPtr;
}

void Piece::addBlockedPiece(Piece* piece) {
	bool isAlreadyBlocked = false;
	for (unsigned int i = 0; i < this->blockedPiecesCount; i++) {
		if (this->blockedSameColorPieces[i] == piece) {
			isAlreadyBlocked = true;
			break;
		}
	}
	if (!isAlreadyBlocked) {
		Piece** oldPtr = this->blockedSameColorPieces;
		this->blockedSameColorPieces = new Piece * [this->blockedPiecesCount + 1];
		for (unsigned int i = 0; i < this->blockedPiecesCount; i++) {
			this->blockedSameColorPieces[i] = oldPtr[i];
		}
		this->blockedSameColorPieces[this->blockedPiecesCount++] = piece;
		delete[] oldPtr;
	}
}

void Piece::removeBlockedPiece(Piece* piece) {
	Piece** oldPtr = this->blockedSameColorPieces;
	this->blockedSameColorPieces = new Piece * [this->blockedPiecesCount - 1];
	unsigned int j = 0;
	for (unsigned int i = 0; i < this->blockedPiecesCount; i++) {
		if (oldPtr[i] != piece) {
			this->blockedSameColorPieces[j++] = oldPtr[i];
		}
	}
	this->blockedPiecesCount--;
	delete[] oldPtr;
}