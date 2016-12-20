/*
  Copyright (C) 2016 by Robin Heinemann. All Rights Reserved.
  archimedes.cpp -- archimedian pi calculation
*/

#include "common.h"

template <typename Float>
void archimedes_pi(i32 doubles) noexcept {
	Float s = sqrt(2);
	Float t = 2;
	i32   n = 4;

	for(i32 i = 0; i < doubles; i++) {
		n *= 2;
		s = sqrt(Float(2) - sqrt(Float(4) - s * s));
		t = (Float(2) / t) * (sqrt(Float(4) + t * t) - Float(2));
		cout << setprecision(16) << s * n / 2 << " <= " << M_PI
			 << " <= " << t * n / 2 << endl;
		cout << setprecision(16)
			 << "Abweichung s: " << Float(1) - (M_PI / (s * (n / 2)))
			 << ", Abweichung t:" << Float(1) - (M_PI / (t * (n / 2))) << endl << endl;
	}
}

i32 main() {
	archimedes_pi<float>(13);
	archimedes_pi<double>(27);
}
