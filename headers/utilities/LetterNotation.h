#pragma once

#ifndef LETTER_NOTATION_H
#define LETTER_NOTATION_H

#include <stdexcept>

char letterNotation(std::uint8_t num) {
	switch (num) {
		case 0: return 'A';
		case 1: return 'B';
		case 2: return 'C';
		case 3: return 'D';
		case 4: return 'E';
		case 5: return 'F';
		case 6: return 'G';
		case 7: return 'H';
		default: throw std::invalid_argument("Invalid letter notation");
	}
};


#endif // !LETTER_NOTATION_H
