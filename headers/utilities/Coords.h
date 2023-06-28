#pragma once

#ifndef COORDS_H
#define COORDS_H

struct Coords {
	char x;
	char y;

	Coords(char y = 0, char x = 0) : x(x), y(y) {}
};

#endif // !COORDS_H