#include "../../headers/special-pieces/Bishop.h"
#include "../../headers/Board.h"

Bishop::Bishop(
	Color color,
	Coords initialCoord,
	Player& player,
	Board& board
) :	Piece(
	color,
	Pieces::BISHOP,
	PieceIDs::BISHOP,
	PieceSymbols::BISHOP,
	PiecePoints::BISHOP,
	initialCoord,
	player,
	board
) {
}

std::pair<Coords*, unsigned int> Bishop::getAvailableMoves() const {
	Coords* availableMoves = new Coords[14];
	unsigned int availableMovesCount = 0;
	Coords newCoords;
	const short boardHeight = this->board.getHeight();
	const short boardWidth = this->board.getWidth();
	bool upRight = true;
	bool upLeft = true;
	bool downRight = true;
	bool downLeft = true;
	for (char i = 1; i < 8; i++) {
		newCoords = { this->coords.y + i, this->coords.x + i };
		if (upRight && 
			newCoords.x >= 0 && newCoords.x < boardWidth && 
			newCoords.y >= 0 && newCoords.y < boardHeight && 
			this->canMove(newCoords)) {
			availableMoves[availableMovesCount++] = newCoords;
		} else {
			upRight = false;
		}
		newCoords = { this->coords.y - i, this->coords.x + i };
		if (downRight && 
			newCoords.x >= 0 && newCoords.x < boardWidth &&
			newCoords.y >= 0 && newCoords.y < boardHeight && 
			this->canMove(newCoords)) {
			availableMoves[availableMovesCount++] = newCoords;
		} else {
			downRight = false;
		}
		newCoords = { this->coords.y - i, this->coords.x - i };
		if (downLeft &&
			newCoords.x >= 0 && newCoords.x < boardWidth &&
			newCoords.y >= 0 && newCoords.y < boardHeight &&
			this->canMove(newCoords)) {
			availableMoves[availableMovesCount++] = newCoords;
		} else {
			downLeft = false;
		}
		newCoords = { this->coords.y + i, this->coords.x - i };
		if (upLeft &&
			newCoords.x >= 0 && newCoords.x < boardWidth &&
			newCoords.y >= 0 && newCoords.y < boardHeight &&
			this->canMove(newCoords)) {
			availableMoves[availableMovesCount++] = newCoords;
		}
		else {
			upLeft = false;
		}
	}

	return std::pair(availableMoves, availableMovesCount);
}

bool Bishop::canMove(Coords coords) const {
	if (this->isMoveAlgorithmSatisfied(coords)) {
		Coords delta = this->getDelta(coords);
		Piece* piece = this->board.pieceAt({ coords.x, coords.y });
		if (piece && !this->isSameColor(piece) || !piece) {
			if (delta.x && delta.y) {
				const char xStart = delta.x < 0 ? coords.x : this->coords.x;
				const char yStart = delta.x < 0 ? coords.y : this->coords.y;
				const char xEnd = delta.x >= 0 ? coords.x : this->coords.x;
				const char yEnd = delta.x >= 0 ? coords.y : this->coords.y;
				std::int8_t yCoef = yEnd < yStart ? -1 : 1;
				for (char i = xStart + 1, j = yStart + yCoef; i < xEnd; i++, j += yCoef) {
					if (this->board.pieceAt({ i, j })) {
						return false;
					}
				}
				return true;
			}
		}
	}
	return false;
}

bool Bishop::isMoveAlgorithmSatisfied(const Coords& coords) const {
	Coords delta = this->getDelta(coords);
	return abs(delta.x) == abs(delta.y);
}