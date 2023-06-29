#pragma once

#ifndef CLICK_DATA_H
#define CLICK_DATA_H

#include <windows.h>

struct ClickData {
	COORD boardPosition;
	unsigned int boardArrayIndex;

	ClickData(SHORT x, SHORT y, unsigned int index) : boardArrayIndex(index) {
		this->boardPosition.X = x;
		this->boardPosition.Y = y;
	};
};

#endif // ! CLICK_DATA_H
