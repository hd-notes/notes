/*
  Copyright (C) 2016 by Robin Heinemann. All Rights Reserved.
  potenz.cpp -- Schneller Algorithmus zur für Integer Exponenten
*/

#include "common.h"

constexpr inline auto sq(f64 x) noexcept -> f64 { return x * x; }


/*
  Es wäre unsinnvoll nicht sq zu verwenden, wenn man nicht das
  Zwischenergebnis von power(x, i / 2) abspeichert, denn dann würde
  man einen bereits berechneten Wert nocheinmal ausrechen, und da dies
  auf allen Ebenen von power passieren würde man anstatt O(n)
  Berechnungen O(2^n) Berechnungen benötigen
 */
constexpr inline auto power(f64 x, i32 i) noexcept -> f64 {
	return (i == 1) ? x
					: (i % 2 == 0) ? sq(power(x, i / 2)) : x * power(x, i - 1);
}

int main() {
	std::cout << power(1.1, 8) << ", " << std::pow(1.1, 8) << std::endl;
	std::cout << power(2.1, 7) << ", " << std::pow(2.1, 7) << std::endl;
	std::cout << power(3.1, 6) << ", " << std::pow(3.1, 6) << std::endl;
	std::cout << power(4.1, 5) << ", " << std::pow(4.1, 5) << std::endl;
	std::cout << power(5.1, 4) << ", " << std::pow(5.1, 4) << std::endl;
	std::cout << power(6.1, 3) << ", " << std::pow(6.1, 3) << std::endl;
	std::cout << power(7.1, 2) << ", " << std::pow(7.1, 2) << std::endl;
	std::cout << power(8.1, 1) << ", " << std::pow(8.1, 1) << std::endl;
}
