#include "../../headers/special-pieces/Queen.h"
#include "../../headers/Board.h"

Queen::Queen(
	Color color,
	Player& player,
	Board& board
) :	Bishop(
		color,
		Fields::D1,
		player,
		board
	),
	Rook(
		color,
		Fields::D1,
		player,
		board
	),
	Piece(
		color,
		Pieces::QUEEN,
		PieceIDs::QUEEN,
		PieceSymbols::QUEEN,
		PiecePoints::QUEEN,
		Fields::D1,
		player,
		board
	) {}

Queen::Queen(
	Color color,
	Coords initialCoords,
	Player& player,
	Board& board
) : Bishop(
	color,
	initialCoords,
	player,
	board
),
Rook(
	color,
	initialCoords,
	player,
	board
),
Piece(
	color,
	Pieces::QUEEN,
	PieceIDs::QUEEN,
	PieceSymbols::QUEEN,
	PiecePoints::QUEEN,
	initialCoords,
	player,
	board
) {}

std::pair<Coords*, unsigned int> Queen::getAvailableMoves(bool updateAttacksAndBlocks, bool considerKingDefence) {
	std::pair<Coords*, unsigned int> bishopMoves = Bishop::getAvailableMoves(updateAttacksAndBlocks, considerKingDefence);
	std::pair<Coords*, unsigned int> rookMoves = Rook::getAvailableMoves(updateAttacksAndBlocks, considerKingDefence);
	Coords* availableMoves = new Coords[bishopMoves.second + rookMoves.second];
	unsigned int availableMovesCount = 0;
	for (unsigned int i = 0; i < bishopMoves.second; i++) {
		availableMoves[availableMovesCount++] = bishopMoves.first[i];
	}
	for (unsigned int i = 0; i < rookMoves.second; i++) {
		availableMoves[availableMovesCount++] = rookMoves.first[i];
	}
	delete bishopMoves.first;
	delete rookMoves.first;
	return std::pair(availableMoves, availableMovesCount);
}

bool Queen::canMove(Coords coords,  bool considerKingDefence) const {
	if (Rook::isMoveAlgorithmSatisfied(coords)) {
		return Rook::canMove(coords, considerKingDefence);
	}
	else if (Bishop::isMoveAlgorithmSatisfied(coords)) {
		return Bishop::canMove(coords, considerKingDefence);
	}
	return false;
}

bool Queen::isMoveAlgorithmSatisfied(const Coords& coords) const {
	return true;
}