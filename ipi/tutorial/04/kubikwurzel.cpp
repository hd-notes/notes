/*
  Copyright (C) 2016 by Robin Heinemann. All Rights Reserved.
  kubikwurzel.cpp -- calculation of cubic root
*/

#include "common.h"

f64 cbrt(f64 y) {
	if(y == 0.0) return 0.0;

	f64 x = y; // inital guess
	f64 x2;
	f64 epsilon = 1e-15 * y;

	while(std::abs(x * x * x - y) > std::abs(epsilon)) {
		x2 = x * x;
		x  = (2 * x2 * x + y) / (3 * x2);
	}

	return x;
}

i32 main() {
	for(const auto & x : {1, 8, 1000, 12983}) {
		// kleiner Fehler erlaubt
		assert(std::abs(cbrt(x) - pow(x, 1.0 / 3.0)) < 1e-15 * x);
		assert(cbrt(-x) == -cbrt(x));
	}
}
