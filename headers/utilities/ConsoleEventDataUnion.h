#pragma once

#ifndef CONSOLE_EVENT_DATA_UNION_H
#define CONSOLE_EVENT_DATA_UNION_H

#include "../utilities/ClickData.h"
#include "../utilities/KeyData.h"

union ConsoleEventDataUnion {
	ClickData clickEventData;
	KeyData keyEventData;

	ConsoleEventDataUnion() {};
};

#endif