/*
  Copyright (C) 2016 by Robin Heinemann. All Rights Reserved.
  pythagoras.cpp -- algorithm to find pythagorean triples
*/

#include "common.h"

bool is_square_slow(i32 n) {
	auto x = std::sqrt(n);
	return x == std::floor(x);
}

bool is_square(i32 n) {
	auto x = n % 4;

	if(x == 1 || x == 0) return is_square_slow(n);

	return false;
}

void pythagorean_triple(i32 max) {
	for(i32 b = 1; b < max; b++) {
		for(i32 a = 1; a < b; a++) {
			if(is_square(a * a + b * b)) {
				std::cout << a << ", " << b << std::endl;
			}
		}
	}
}

i32 main() { pythagorean_triple(400); }
