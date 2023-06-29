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
	name(PiecesToString(name)),
	id(PieceIDsToString(id)),
	symbol(PieceSymbolToString(symbol)),
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

int Piece::getConsoleColor() {
	if (this->isBlack()) {
		return 0;
	}

	return FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
}

Coords Piece::addDelta(Coords delta) {
	this->coords.x += delta.x;
	this->coords.y += delta.y;
	return this->coords;
}

bool Piece::move(Coords coords) {
	if (this->canMove(coords)) {
		this->board.move(this->coords, coords);
		this->coords = coords;
		return true;
	}
	return false;
}

bool Piece::isOwnedBy(const Player* player) {
	return player == &this->owner;
}