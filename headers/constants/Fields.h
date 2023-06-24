#pragma once

#ifndef FIELDS_H
#define FIELDS_H

#include "../utilities/Coords.h"

namespace Fields {
	// White King
	const Coords E1 = Coords(0, 4);

	// White Queen
	const Coords D1 = Coords(0, 3);

	// White Rooks
	const Coords A1 = Coords(0, 0);
	const Coords H1 = Coords(0, 7);

	// White Bishops
	const Coords C1 = Coords(0, 2);
	const Coords F1 = Coords(0, 5);

	// White Knights
	const Coords B1 = Coords(0, 1);
	const Coords G1 = Coords(0, 6);

	// White Pawns
	const Coords A2 = Coords(1, 0);
	const Coords B2 = Coords(1, 1);
	const Coords C2 = Coords(1, 2);
	const Coords D2 = Coords(1, 3);
	const Coords E2 = Coords(1, 4);
	const Coords F2 = Coords(1, 5);
	const Coords G2 = Coords(1, 6);
	const Coords H2 = Coords(1, 7);

}

#endif // !FIELDS_H