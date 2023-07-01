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
#include "constants/PiecePoints.h"

class Player;
class Board;

class Piece {
protected:
	bool isMoved = false;
	Color color;
	std::string name;
	std::string id;
	std::string symbol;
	Coords coords;
	Player& owner;
	Board& board;
	int cyclesStandingWithoutAMove = 0;
	int cyclesFromGameStart = 0;
	int points = 0;
public:
	Piece(
		Color color,
		Pieces name,
		PieceIDs id,
		PieceSymbols symbol,
		int points,
		Coords initialCoords,
		Player& owner,
		Board& board,
		bool isSecondLine = false
	);
	std::string getId();
	virtual std::string getSymbol();
	virtual std::pair<Coords*, unsigned int> getAvailableMoves() const = 0;
	virtual bool isMoveAlgorithmSatisfied(const Coords& coords) const = 0;
	virtual bool canMove(Coords coords) const = 0;
	virtual int getConsoleColor();
	virtual ~Piece() = default;
	virtual bool move(Coords coords);
	virtual void incrementCycles();
	virtual void incrementNoMoveCycles();
	Coords addDelta(Coords);
	bool isWhite() const;
	bool isBlack() const;
	bool isUnknown() const;
	bool isOwnedBy(const Player* player);
	Player& getOwner();
	Board& getBoard();
	Coords getCoords();
	Coords getDelta(const Coords& coords) const;
	Coords getColorBasedDelta(const Coords& coords) const;
	bool hasMoved() const;
	int getCycles();
	int getNoMoveCycles();
	bool isSameColor(Piece* piece) const;
	int getPoints();
};

#endif // !PIECE_H