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
	const unsigned int arrayLength = this->height * this->width;
	this->board = new Slot[arrayLength]();
	
	for (unsigned int i = 0; i < arrayLength; i++) {
		char x = i % this->width;
		char y = i / this->width;
		this->board[i].setCoords({ y, x });
	}
}

void Board::placePieces(Piece** pieces, unsigned char count) {
	for (unsigned char i = 0; i < count; i++) {
		const Coords coordinates = pieces[i]->getCoords();
		const std::uint8_t x = coordinates.x;
		const std::uint8_t y = coordinates.y;
		this->board[x + (y * this->width)].setPiece(pieces[i]);
	}
}

void Board::draw(bool wasMove) const {
	this->console.clear();
	this->console.drawBoard(wasMove);
}

Piece* Board::move(Coords from, Coords to) {
	const unsigned short initialIndex = from.x + from.y * this->width;
	const unsigned short finalIndex = to.x + to.y * this->width;
	Piece* pieceToMove = this->board[initialIndex].removePiece();
	return this->board[finalIndex].setPiece(pieceToMove);
}

Piece* Board::pieceAt(unsigned short index) const {
	if (index >= this->width * this->height) {
		throw std::invalid_argument("Invalid board index");
	}
	return this->board[index].getPiece();
}

Piece* Board::pieceAt(COORD coords) const {
	if (coords.X >= this->width || coords.Y >= this->height) {
		throw std::invalid_argument("Invalid board coords");
	}
	return this->board[coords.Y * this->height + coords.X].getPiece();
}

bool Board::click(unsigned short index) {
	if (index >= this->width * this->height) {
		throw std::invalid_argument("Invalid board index");
	}
	Piece* clickedPiece = this->board[index].getPiece();
	if (clickedPiece && !this->selectedPiece) {
		this->selectedPiece = clickedPiece;
	} else if (this->selectedPiece) {
		char x = index % this->width;
		char y = index / this->width;
		bool wasMove = this->selectedPiece->move({ y, x });
		this->selectedPiece = nullptr;
		return wasMove;
	}
	return false;
}

bool Board::click(COORD coords) {
	if (coords.X >= this->width || coords.Y >= this->height) {
		throw std::invalid_argument("Invalid board coords");
	}
	return this->click(coords.Y * this->height + coords.X);
}

bool Board::isPieceSelected() {
	return !!this->selectedPiece;
};

short Board::getHeight() {
	return this->height;
}

short Board::getWidth() {
	return this->width;
}

Piece* Board::removePiece(Coords coords) {
	const unsigned short index = coords.x + coords.y * this->width;
	return this->board[index].removePiece();
}