#pragma once

#ifndef PLAYER_STATS_H
#define PLAYER_STATS_H

#include "../Piece.h"

struct PlayerStats {
	int score = 0;
	int movesCount = 0;
	int capturesCount = 0;
	int checksCount = 0;
	int eatenPoints = 0;
	int eatenPiecesCount = 0;
	Piece** eatenPieces = nullptr;
};

#endif // !PLAYER_STATS_H
