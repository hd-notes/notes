/*
  Copyright (C) 2016 by Robin Heinemann. All Rights Reserved.
  weekday.cpp -- Wochentagberechnung
*/

#include <cmath>
#include <cassert>
#include <cinttypes>
#include <iostream>
#include <string>

using i32 = std::int32_t;
using str = std::string;

i32 sgn(i32 x) { return (x != 0) ? x / std::abs(x) : 0; }

i32 floorDiv(i32 a, i32 b) {
	// i32 c = ((sgn(a) + sgn(b)) / 2) * (- 2 * a) + ((((sgn(a) + sgn(b)) / 2) + 1) % 2) * ( (a % b) b);
	i32 c = (a % b) != 0 ? std::abs(b) : 0;
	return (a / b) > 0 ? a / b : -(std::abs(a) + c) / std::abs(b);
}

bool gap_year(i32 y) {
	return ((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0);
}

i32 weekday2001(i32 d, i32 m, i32 y) {
	i32 z  = y - 2001;
	i32 j1 = (365 * z + (z / 4) - (z / 100) + (z / 400)) % 7;
	i32 p =
		(m == 1) ? d : ((m == 2) ? d + 31
								 : (((m > 2) && !gap_year(y))
										? (d + 59 + ((153 * m - 457) / 5))
										: (d + 60 + ((153 * m - 457) / 5))));
	return (j1 + p - 1) % 7;
}

int main() {
	assert(weekday2001(1, 1, 2002) == 1);
	assert(weekday2001(7, 2, 2001) == 2);
	assert(weekday2001(12, 7, 2008) == 5);
	assert(weekday2001(28, 2, 2016) == 6);
	assert(weekday2001(10, 11, 2016) == 3);
	assert(weekday2001(10, 11, 2004) == 2);

	for(int i = -100; i < 100; i++) {
		for(int j = -100; j < 100; j++) {
			if(j == 0) continue;
			std::cout << i << ", " << j << std::endl;
			std::cout << floorDiv(i,j) << std::endl;
			std::cout << (int) floor((double) i / (double) j) << std::endl;
			std::cout << floorDiv(j,i) << std::endl;
			std::cout << (int) floor((double) j / (double) i) << std::endl;
			assert(floorDiv(i,j) == (int) floor((double) i / (double) j));
			assert(floorDiv(j,i) == (int) floor((double) j / (double) i));
		}
	}
}
