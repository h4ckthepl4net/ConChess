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
		this->board.move(this->coords, coords);
		this->coords = coords;
		this->isMoved = true;
		this->cyclesStandingWithoutAMove = 0;
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