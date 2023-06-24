#include "../headers/Game.h"


Game::Game(unsigned char playerCount): board(this->console) {
	this->initPlayers(playerCount);
}

void Game::initPlayers(unsigned char playerCount) {
	this->players = new Player[playerCount];
	this->playerCount = playerCount;
}

void Game::preparePlayers() {
	for (unsigned char i = 0; i < this->playerCount; i++) {
		std::string name;
		std::cout << "Enter player " << i + 1 << " name: ";
		std::cin >> name;
		this->players[i].setName(name);
		this->players[i].setColor(static_cast<Color>(i));
		this->players[i].initPieces();
	}
}

void Game::prepareBoard() {
	this->board.initBoard();

	Piece** player1Pieces = this->players[0].getPieces();
	const unsigned char player1PiecesCount = this->players[0].getPiecesCount();
	Piece** player2Pieces = this->players[1].getPieces();
	const unsigned char player2PiecesCount = this->players[1].getPiecesCount();
	this->board.placePieces(player1Pieces, player1PiecesCount);
	this->board.placePieces(player2Pieces, player2PiecesCount);
}