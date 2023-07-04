#include "../headers/Console.h"
#include "../headers/Board.h"
#include "../headers/utilities/LetterNotation.h"
#include "../headers/utilities/ConsoleEventType.h"
#include "../headers/utilities/ConsoleEventDataUnion.h"

const COORD Console::actualBoardOffset = { 3, 1 };

Console::Console(
	Board& board,
	unsigned short height,
	unsigned short width,
	HANDLE externalOutputHandle,
	HANDLE externalInputHandle,
	CONSOLE_SCREEN_BUFFER_INFOEX externalConsoleInfo
): board(board), height(height), width(height) {
	this->hOutConsole = externalOutputHandle ? externalOutputHandle : GetStdHandle(STD_OUTPUT_HANDLE);
	this->hInConsole = externalInputHandle ? externalInputHandle : GetStdHandle(STD_INPUT_HANDLE);
	this->consoleInfo = externalConsoleInfo;
	if (this->consoleInfo.cbSize == 0) {
		this->consoleInfo.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
		GetConsoleScreenBufferInfoEx(this->hOutConsole, &this->consoleInfo);
	}
}

void Console::drawRawTile(std::string tileContent, int contentColor) const {
	SetConsoleTextAttribute(this->hOutConsole, contentColor);
	std::cout << ' ' << tileContent;
};
void Console::drawBlackTile(std::string tileContent, int contentColor) const {
	this->drawRawTile(tileContent, FOREGROUND_INTENSITY | contentColor);
};
void Console::drawWhiteTile(std::string tileContent, int contentColor) const {
	this->drawRawTile(tileContent, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_INTENSITY | contentColor);
};
void Console::drawBlackTile(char tileContent, int contentColor) const {
	this->drawBlackTile(std::string(1, tileContent), contentColor);
};
void Console::drawWhiteTile(char tileContent, int contentColor) const {
	this->drawWhiteTile(std::string(1, tileContent), contentColor);
};

void Console::notateHorizontalFrame(std::uint8_t offsetY) const {
	const std::uint8_t offsetX = 3;
	const unsigned int boardWidth = this->board.width;
	COORD cursorPos = { offsetX,offsetY };
	SetConsoleCursorPosition(this->hOutConsole, cursorPos);
	for (unsigned int i = 0; i < boardWidth; i++) {
		this->drawWhiteTile(letterNotation(i));
	}
};
void Console::notateSideFrame(std::uint8_t offsetX) const {
	std::uint8_t offsetY = 1;
	const unsigned int boardHeight = this->board.height;
	COORD cursorPos = { offsetX,0 };
	for (unsigned int i = 0; i < boardHeight; i++) {
		cursorPos.Y = i + offsetY;
		SetConsoleCursorPosition(this->hOutConsole, cursorPos);
		this->drawWhiteTile('0' + boardHeight - i);
		std::cout << ' ';
	}
};

void Console::clear() const {
	DWORD inConsoleMode = 0;
	DWORD outConsoleMode = 0;
	GetConsoleMode(this->hInConsole, &inConsoleMode);
	GetConsoleMode(this->hOutConsole, &outConsoleMode);
	SetConsoleTextAttribute(this->hOutConsole, 0);
	system("cls");
	SetConsoleMode(this->hInConsole, inConsoleMode);
	SetConsoleMode(this->hOutConsole, outConsoleMode);
}

void Console::prepare() const {
	SetConsoleMode(this->hInConsole, ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT | ENABLE_EXTENDED_FLAGS);
}

void Console::drawBoard(bool wasMove) const {
	const unsigned int width = this->board.width;
	const unsigned int height = this->board.height;
	Slot* board = this->board.board;
	const Console& self = *this;
	self.notateHorizontalFrame(0);
	self.notateSideFrame(0);
	COORD cursorPos = this->actualBoardOffset;
	unsigned int arrayPos;
	for (int i = height - 1; i >= 0; i--) {
		SetConsoleCursorPosition(this->hOutConsole, cursorPos);
		for (unsigned int j = 0; j < width; j++) {
			arrayPos = (i * width + j);
			Piece* piece = board[arrayPos].getPiece();
			std::string symbol = " ";
			int color = 0;
			if (piece) {
				if (wasMove) {
					piece->incrementNoMoveCycles();
					piece->incrementCycles();
				}
				symbol = piece->getSymbol();
				color = piece->getConsoleColor();
			}
			if (this->board.isPossibleMove(arrayPos)) {
				const int tileColor = color | ((piece) ? BACKGROUND_RED : BACKGROUND_GREEN);
				self.drawRawTile(symbol, tileColor);
			} else {
				if ((i + j) % 2 == 0) {
					self.drawBlackTile(symbol, color);
				} else {
					self.drawWhiteTile(symbol, color);
				}
			}
			if (j == width - 1) {
				cursorPos.Y++;
				cursorPos.X = 3;
			}
		}
	}
	self.notateSideFrame(3 + 2 * width);
	self.notateHorizontalFrame(1 + height);
	std::cout << std::endl;
}

void Console::drawPlayerStats(Player* players, unsigned int count) const {
	std::cout << std::endl;
	const char* colors[2] = { "W", "B" };
	const Console& self = *this;
	for (unsigned int i = 0; i < count; i++) {
		Player& player = players[i];
		std::string name = player.getName();
		int score = player.stats.score;
		int points = player.stats.eatenPoints;
		int eatenCount = player.stats.eatenPiecesCount;
		Color color = player.getColor();
		std::string colorName = colors[static_cast<unsigned int>(color)];
		std::cout << " (" << colorName << ") " << name;
		std::cout << " | Score: " << score;
		if (eatenCount > 0) {
			std::cout << " | Has eaten (" << points << " Points) (" << eatenCount << " Pieces)";
		}
		std::cout << "  " << std::endl;
	}
}

ConsoleEvent Console::listen(bool getProcessedPos) const {
	DWORD numberOfReadRecords;
	INPUT_RECORD mouseInput;

	while (true) {
		ReadConsoleInput(this->hInConsole, &mouseInput, 1, &numberOfReadRecords);
		switch (mouseInput.EventType) {
			case KEY_EVENT:
				// TODO handle this event or disregard
				break;
			case MOUSE_EVENT:
				MOUSE_EVENT_RECORD mouseEvent = mouseInput.Event.MouseEvent;
				COORD position = mouseEvent.dwMousePosition;
				if (mouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED && !(mouseEvent.dwEventFlags & MOUSE_MOVED)) {
					if (getProcessedPos) {
						short boardX, boardY;
						boardX = static_cast<short>(floor(static_cast<float>(position.X - this->actualBoardOffset.X) / 2));
						boardY = this->board.height - 1 - (position.Y - this->actualBoardOffset.Y);
						if (boardX < this->board.width && boardY < this->board.height &&
							boardX >= 0 && boardY >= 0) {
							ConsoleEventDataUnion data;
							data.clickEventData.boardArrayIndex = boardY * this->board.width + boardX;
							data.clickEventData.boardPosition.X = boardX;
							data.clickEventData.boardPosition.Y = boardY;
							return ConsoleEvent(ConsoleEventType::CLICK, data);
						}
					}
					else {
						ConsoleEventDataUnion data;
						data.clickEventData.boardPosition.X = position.X;
						data.clickEventData.boardPosition.Y = position.Y;
						return ConsoleEvent(ConsoleEventType::CLICK, data);
					}
				}
				break;
			case WINDOW_BUFFER_SIZE_EVENT:// TODO Handle resize here
				break;
		}
	}
}

int Console::drawPromptAndListen(std::string prompt, ConsoleButton* buttonArray, unsigned int buttonCount) const {
	this->clear();
	SetConsoleTextAttribute(this->hOutConsole, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	const Console& self = *this;
	std::cout << prompt << std::endl;
	for (unsigned int i = 0; i < buttonCount; i++) {
		std::cout << " " << i + 1 << " - " << buttonArray[i].caption << std::endl;
	}
	std::cout << std::endl;
	while (true) {
		ConsoleEvent event = self.listen(false);
		if (event.type == ConsoleEventType::CLICK) {
			for (unsigned int i = 0; i < buttonCount; i++) {
				if (event.data.clickEventData.boardPosition.Y == i + 1) {
					return buttonArray[i].id;
				}
			}
		}
	}
}

void Console::drawGameOver(Player* lostPlayer) const {
	this->clear();
	SetConsoleTextAttribute(this->hOutConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
	std::cout << "Game Over!" << std::endl;
	std::cout << "Player " << lostPlayer->getName() << " has lost!" << std::endl;
}