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
	this->board = new Piece*[height];
}

void Board::placePieces(Piece** pieces, unsigned char count) {
	for (unsigned char i = 0; i < count; i++) {
		const Coords coordinates = pieces[i]->getCoords();
		const unsigned char x = coordinates.x;
		const unsigned char y = coordinates.y;
		this->board[x * y] = pieces[i];
	}
}

void Board::draw() const {
	this->console.clear();
	this->console.drawBoard();
}

bool Board::move(Coords from, Coords to) {
	return false;
}