#pragma once

#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>
#include <windows.h>

class Console {
public:
	Console(unsigned short = 17, unsigned short = 17);
	void drawBoard() const;
	void clear() const;
};


#endif // !CONSOLE_H

