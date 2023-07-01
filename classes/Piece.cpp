#include "../headers/Piece.h"
#include "../headers/Board.h"

Piece::Piece(
	Color color,
	Pieces name,
	PieceIDs id,
	PieceSymbols symbol,
	Coords initialCoords,
	Player& player,
	Board& board,
	bool isSecondLine
) :
	color(color),
	name(piecesToString(name)),
	id(pieceIDsToString(id)),
	symbol(pieceSymbolToString(symbol)),
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

bool Piece::isWhite() {
	return this->color == Color::WHITE;
}

bool Piece::isBlack() {
	return this->color == Color::BLACK;
}

bool Piece::isUnknown() {
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
		this->board.move(this->coords, coords);
		this->coords = coords;
		this->isMoved = true;
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

bool Piece::hasMoved() {
	return this->isMoved;
}