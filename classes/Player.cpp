#include "../headers/Player.h"

Player::Player(std::string name) {
	this->setName(name);
}

std::string Player::getName() {
	return this->name;
}

Color Player::getColor() {
	return this->color;
}

Piece* Player::getKing() {
	return this->king;
}

Piece** Player::getPieces() {
	return this->pieces;
}

unsigned char Player::getPiecesCount() {
	return this->piecesCount;
}

void Player::setBoard(Board* board) {
	this->board = board;
}

void Player::setColor(Color color) {
	this->color = color;
}

void Player::setName(std::string name) {
	this->name = name;
}

void Player::initPieces(unsigned char count) {
	if (count < 16) {
		throw std::invalid_argument("Piece count cannot be smaller than 16");
	}

	this->pieces = new Piece*[count];

	this->king = new King(
		this->color,
		*this,
		*board
	);

	this->pieces[0] = this->king;

	this->pieces[1] = new Queen(
		this->color,
		*this,
		*board
	);

	const Coords bishopCoords[2] = { Fields::C1, Fields::F1 };
	for (std::uint8_t i = 2; i < 4; i++) {
		this->pieces[i] = new Bishop(
			this->color,
			bishopCoords[i - 2],
			*this,
			*board
		);
	}

	const Coords knightCoords[2] = { Fields::B1, Fields::G1 };
	for (std::uint8_t i = 4; i < 6; i++) {
		this->pieces[i] = new Knight(
			this->color,
			knightCoords[i-4],
			*this,
			*board
		);
	}

	const Coords rookCoords[2] = { Fields::A1, Fields::H1 };
	for (std::uint8_t i = 6; i < 8; i++) {
		this->pieces[i] = new Rook(
			this->color,
			rookCoords[i - 6],
			*this,
			*board
		);
	}

	const Coords pawnCoords[8] = { Fields::A2, Fields::B2, Fields::C2, Fields::D2, Fields::E2, Fields::F2, Fields::G2, Fields::H2 };
	for (std::uint8_t i = 8; i < 16; i++) {
		this->pieces[i] = new Pawn(
			this->color,
			pawnCoords[i - 8],
			*this,
			*board
		);
	}
}

Player::~Player() {
	// TODO implement destructor to delete all pieces
	delete[] this->pieces;
}


