#pragma once

#ifndef CONSOLE_BUTTON_H
#define CONSOLE_BUTTON_H

#include <string>

struct ConsoleButton {
	int id;
	std::string caption;

	ConsoleButton(int id, std::string caption) : id(id), caption(caption) {};
};

#endif // !CONSOLE_BUTTON_H