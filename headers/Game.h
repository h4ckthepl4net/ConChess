#pragma once

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "Board.h"
#include "Console.h"
#include "Player.h"

class Game {
	Board board;
	Console console;
	Player* playerToPlay;
	Player* players;
	unsigned char playerCount;

	void initPlayers(unsigned char);
	void prepareConsoleForGame();
public:
	Game(unsigned char playerCount = 2);
	void preparePlayers();
	void prepareBoard();
	void start();
};

#endif // !GAME_H