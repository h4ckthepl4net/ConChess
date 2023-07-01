#pragma once

#ifndef POSSIBLE_MOVE_H
#define POSSIBLE_MOVE_H

#include "../Piece.h"
#include <windows.h>

class PossibleMove : public Piece {
	Piece* internalPiece = nullptr;
public:
	PossibleMove(Piece* piece);

	virtual int getConsoleColor() override;
	virtual std::string getSymbol() override;

	Coords* getAvailableMoves() const override;
	bool canMove(Coords coords) const override;

	Piece* getInternalPiece() const;
};

#endif