#pragma once

#ifndef CONSOLE_EVENT_H
#define CONSOLE_EVENT_H

#include "../utilities/ConsoleEventType.h"
#include "../utilities/ConsoleEventDataUnion.h"

struct ConsoleEvent {
	ConsoleEventType type;
	ConsoleEventDataUnion data;

	ConsoleEvent() : type(ConsoleEventType::UNKNOWN) {};
	ConsoleEvent(ConsoleEventType type, ConsoleEventDataUnion data) : type(type), data(data) {}
};


#endif // !CONSOLE_EVENT_H

