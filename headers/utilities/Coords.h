#pragma once

#ifndef COORDS_H
#define COORDS_H

struct Coords {
	char x;
	char y;

	Coords(char x = 0, char y = 0) : x(x), y(y) {}
};

#endif // !COORDS_H