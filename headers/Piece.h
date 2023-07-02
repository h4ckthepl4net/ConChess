#pragma once

#ifndef PIECE_H
#define PIECE_H

#include <string>
#include <limits>

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
class Slot;

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
	Piece** blockedSameColorPieces = nullptr;
	unsigned int blockedPiecesCount = 0;
	Slot** attackedSlots = nullptr;
	unsigned int attackedSlotsCount = 0;
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
	virtual std::pair<Coords*, unsigned int> getAvailableMoves(bool = false) = 0;
	virtual bool isMoveAlgorithmSatisfied(const Coords& coords) const = 0;
	virtual bool canMove(Coords coords) const = 0;
	virtual int getConsoleColor();
	virtual ~Piece() = default;
	virtual bool move(Coords coords);
	virtual void incrementCycles();
	virtual void incrementNoMoveCycles();
	virtual bool considerChecked(const Coords&) const;
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
	bool isSameColor(const Piece* piece) const;
	int getPoints();
	void setCoords(Coords);
	void addAttackedSlot(Slot*);
	void removeAttackedSlot(Slot*);
	void addBlockedPiece(Piece*);
	void removeBlockedPiece(Piece*);
};

#endif // !PIECE_H