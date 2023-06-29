#include "../headers/Board.h"

Board::Board(
	Console& console,
	unsigned short height,
	unsigned short width
):
	console(console),
	width(width),
	height(height) {
}

void Board::initBoard() {
	this->board = new Piece*[this->height * this->width]();
}

void Board::placePieces(Piece** pieces, unsigned char count) {
	for (unsigned char i = 0; i < count; i++) {
		const Coords coordinates = pieces[i]->getCoords();
		const unsigned char x = coordinates.x;
		const unsigned char y = (this->height + coordinates.y) % this->height;
		this->board[x + (y * this->width)] = pieces[i];
	}
}

void Board::draw() const {
	this->console.clear();
	this->console.drawBoard();
}

bool Board::move(Coords from, Coords to) {
	return false;
}

Piece* Board::pieceAt(unsigned int index) {
	if (index >= this->width * this->height) {
		throw std::invalid_argument("Invalid board index");
	}
	return this->board[index];
}

Piece* Board::pieceAt(COORD coords) {
	if (coords.X >= this->width || coords.Y >= this->height) {
		throw std::invalid_argument("Invalid board coords");
	}
	return this->board[coords.Y * this->height + coords.X];
}