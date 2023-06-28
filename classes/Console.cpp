#include "../headers/Console.h"
#include "../headers/Board.h"
#include "../headers/utilities/LetterNotation.h"

Console::Console(
	Board& board,
	unsigned short height,
	unsigned short width,
	HANDLE externalHandle,
	CONSOLE_SCREEN_BUFFER_INFOEX externalConsoleInfo
): board(board), height(height), width(height) {
	this->hConsole = externalHandle ? externalHandle : GetStdHandle(STD_OUTPUT_HANDLE);
	this->consoleInfo = externalConsoleInfo;
	if (this->consoleInfo.cbSize == 0) {
		this->consoleInfo.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
		GetConsoleScreenBufferInfoEx(this->hConsole, &this->consoleInfo);
	}
}

void Console::drawBlackTile(std::string tileContent, int contentColor) const {
	SetConsoleTextAttribute(this->hConsole, FOREGROUND_INTENSITY | contentColor);
	std::cout << ' ' << tileContent;
};
void Console::drawWhiteTile(std::string tileContent, int contentColor) const {
	SetConsoleTextAttribute(this->hConsole, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_INTENSITY | contentColor);
	std::cout << ' ' << tileContent;
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
	SetConsoleCursorPosition(this->hConsole, cursorPos);
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
		SetConsoleCursorPosition(this->hConsole, cursorPos);
		this->drawWhiteTile('0' + boardHeight - i);
		std::cout << ' ';
	}
};

void Console::clear() const {
	system("cls");
}

void Console::prepare() const {
	SetConsoleMode(this->hConsole, ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT);
}

void Console::drawBoard() const {
	const unsigned int width = this->board.width;
	const unsigned int height = this->board.height;
	Piece** board = this->board.board;
	const Console& self = *this;
	self.notateHorizontalFrame(0);
	self.notateSideFrame(0);
	COORD cursorPos = { 3,1 };
	unsigned int arrayPos;
	for (int i = height - 1; i >= 0; i--) {
		SetConsoleCursorPosition(this->hConsole, cursorPos);
		for (int j = 0; j < width; j++) {
			arrayPos = (i * width + j);
			Piece* piece = board[arrayPos];
			std::string symbol = piece ? piece->getSymbol() : " ";
			int color = piece ? piece->getConsoleColor() : 0;
			if ((i + j) % 2 == 0) {
				self.drawBlackTile(symbol, color);
			} else {
				self.drawWhiteTile(symbol, color);
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