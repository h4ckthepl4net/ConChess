#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "Piece.h"

#include "constants/Pieces.h"
#include "constants/PieceIDs.h"
#include "constants/PieceSymbols.h"

#include "special-pieces/King.h"
#include "special-pieces/Queen.h"
#include "special-pieces/Bishop.h"
#include "special-pieces/Knight.h"
#include "special-pieces/Rook.h"
#include "special-pieces/Pawn.h"

class Player {
	Color color;
	std::string name;
	Piece* king = nullptr;
	Piece** pieces = nullptr;
	unsigned char piecesCount = 16;
	Board* board = nullptr;
public:
	Player(std::string = "");
	std::string getName();
	Piece* getKing();
	Piece** getPieces();
	unsigned char getPiecesCount();
	void setBoard(Board*);
	void setColor(Color);
	void setName(std::string);
	void initPieces(unsigned char = 16);
	~Player();
};

#endif // !PLAYER_H
