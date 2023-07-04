#include "../headers/Game.h"


Game::Game(unsigned char playerCount): board(this->console), console(this->board) {
	this->initPlayers(playerCount);
}

void Game::initPlayers(unsigned char playerCount) {
	this->players = new Player[playerCount];
	this->playerCount = playerCount;
}

void Game::prepareConsoleForGame() {
	this->console.prepare();
	// TODO resize and prevent resizing by user
}

void Game::preparePlayers() {
	for (unsigned char i = 0; i < this->playerCount; i++) {
		std::string name;
		std::cout << "Enter player " << i + 1 << " name: ";
		std::cin >> name;
		this->players[i].setName(name);
		this->players[i].setColor(static_cast<Color>(i));
		this->players[i].setBoard(&this->board);
		this->players[i].initPieces();
	}
	this->playerToPlay = &this->players[0];
}

void Game::prepareBoard() {
	this->board.initBoard();

	Piece** player1Pieces = this->players[0].getPieces();
	const unsigned char player1PiecesCount = this->players[0].getPiecesCount();
	Piece** player2Pieces = this->players[1].getPieces();
	const unsigned char player2PiecesCount = this->players[1].getPiecesCount();
	this->board.placePieces(player1Pieces, player1PiecesCount);
	this->board.placePieces(player2Pieces, player2PiecesCount);
	for (unsigned int i = 0; i < player1PiecesCount; i++) {
		player1Pieces[i]->getAvailableMoves(true);
	}
	for (unsigned int i = 0; i < player2PiecesCount; i++) {
		player2Pieces[i]->getAvailableMoves(true);
	}
}

void Game::start() {
	this->prepareConsoleForGame();
	ConsoleEvent event;
	bool wasMove = false;
	do {
		this->board.draw(wasMove);
		this->console.drawPlayerStats(this->players, this->playerCount);
		Piece* clickedPiece = nullptr;
		do {
			event = this->console.listen();
			clickedPiece = this->board.pieceAt(event.data.clickEventData.boardArrayIndex);
		} while (!this->board.isPieceSelected() &&
				(clickedPiece == nullptr || !clickedPiece->isOwnedBy(this->playerToPlay)));
		wasMove = this->board.click(event.data.clickEventData.boardArrayIndex);
		if (wasMove) {
			const std::uint8_t currentIndex = static_cast<std::uint8_t>(this->playerToPlay - this->players);
			const std::uint8_t nextPlayer = currentIndex != 0 ? currentIndex % (this->playerCount-1) : currentIndex + 1;
			this->playerToPlay = this->players + nextPlayer;

			if (this->board.isCheckmate(this->playerToPlay)) {
				this->console.drawGameOver(this->playerToPlay);
				break;
			}
		}
	} while (true);
}