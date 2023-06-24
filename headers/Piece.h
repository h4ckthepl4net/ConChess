#pragma once

#ifndef PIECE_H
#define PIECE_H

#include <string>
#include "constants/Pieces.h"
#include "constants/PieceIDs.h"
#include "constants/PieceSymbols.h"
#include "utilities/Color.h"
#include "utilities/Coords.h"

#include "constants/Fields.h"
#include "constants/FieldDeltas.h"

class Player;
class Board;

class Piece {
protected:
	Color color;
	std::string name;
	std::string id;
	std::string symbol;
	Coords coords;
	Player& owner;
	Board& board;
public:
	Piece(
		Color color,
		Pieces name,
		PieceIDs id,
		PieceSymbols symbol,
		Coords initialCoords,
		Player& owner,
		Board& board,
		bool isSecondLine = false
	);
	virtual Coords* getAvailableMoves() const = 0;
	virtual bool canMove(Coords coords) const = 0;
	virtual ~Piece() = default;
	Coords addDelta(Coords);
	bool move(Coords coords);
	bool isWhite();
	bool isBlack();
	Coords getCoords();
};

#endif // !PIECE_H