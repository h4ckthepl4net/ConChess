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
	if (this->canMove(coords) && this->considerChecked(coords)) {
		Piece* eatenPiece = this->board.move(this->coords, coords);
		Coords oldCoords = this->coords;
		this->coords = coords;
		this->isMoved = true;
		this->cyclesStandingWithoutAMove = 0;
		if (eatenPiece) {
			this->owner.addEatenPiece(eatenPiece);
		}
		for (unsigned int i = 0; i < this->attackedSlotsCount; i++) {
			this->removeAttackedSlot(this->attackedSlots[i]);
		}
		for (unsigned int i = 0; i < this->blockedPiecesCount; i++) {
			this->removeBlockedPiece(this->blockedSameColorPieces[i]);
		}
		this->board.slotAt(oldCoords)->recalculateAttacks();
		this->board.slotAt(coords)->recalculateAttacks();
		this->getAvailableMoves(true);
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

bool Piece::isSameColor(const Piece* piece) const {
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
	slot->removeAttackedBy(this);
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

bool Piece::considerChecked(const Coords& coords) const {
	King* king = static_cast<King*>(this->owner.getKing());
	Coords kingCoords = king->getCoords();
	Slot* kingSlot = this->board.slotAt(kingCoords);
	return !kingSlot->isAttacked() || kingSlot->moveWillCoverAllAttacks(coords);
}

bool Piece::considerKingDefense() const {
	Coords kingCoords = this->owner.getKing()->getCoords();
	Slot* currentSlot = this->board.slotAt(this->coords);
	Piece* oldPiece = currentSlot->removePiece();
	std::pair<Piece **, const unsigned int> attackers = currentSlot->getAttackedBy();
	for (unsigned int i = 0; i < attackers.second; i++) {
		if (!attackers.first[i]->isSameColor(oldPiece)) {
			std::pair<Coords*, unsigned int> moves = attackers.first[i]->getAvailableMoves(false, false);
			for (unsigned int j = 0; j < moves.second; j++) {
				if (moves.first[j].x == kingCoords.x && moves.first[j].y == kingCoords.y) {
					currentSlot->setPiece(oldPiece);
					delete[] attackers.first;
					delete[] moves.first;
					return false;
				}
			}
			delete[] moves.first;
		}
	}
	currentSlot->setPiece(oldPiece);
	delete[] attackers.first;
	return true;
}

void Piece::clearAttackedSlots() {
	for (unsigned int i = 0; i < this->attackedSlotsCount; i++) {
		this->attackedSlots[i]->removeAttackedBy(this);
	}
	delete[] this->attackedSlots;
	this->attackedSlots = nullptr;
	this->attackedSlotsCount = 0;
}

void Piece::clearBlockedPieces() {
	delete[] this->blockedSameColorPieces;
	this->blockedSameColorPieces = nullptr;
	this->blockedPiecesCount = 0;
}

void Piece::recalculateAttackedSlots() {
	this->clearBlockedPieces();
	this->clearAttackedSlots();
	this->getAvailableMoves(true);
}