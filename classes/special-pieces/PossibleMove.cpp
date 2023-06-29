#include "../../headers/special-pieces/PossibleMove.h"

PossibleMove::PossibleMove(
	Piece* piece,
	Coords coord,
	Player& player,
	Board& board
) : Piece(
	Color::UNKNOWN,
	Pieces::POSSIBLE_MOVE,
	PieceIDs::POSSIBLE_MOVE,
	PieceSymbols::POSSIBLE_MOVE,
	coord,
	player,
	board
) {}