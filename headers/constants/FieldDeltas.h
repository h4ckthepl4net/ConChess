#pragma once

#ifndef FIELD_DELTAS_H
#define FIELD_DELTAS_H

#include "../utilities/Coords.h"

namespace FieldDeltas {
	// First line pieces delta
	const Coords FirstLine = { 0, -1 };

	// Second line pieces delta
	const Coords SecondLine = { 0, -3 };

}

#endif // !FIELD_DELTAS_H