/*
  Copyright (C) 2016 by Robin Heinemann. All Rights Reserved.
  weekday.cpp -- Wochentagberechnung
*/

#include "common.h"

i32 sgn(i32 x) { return (0 < x) - (x < 0); }

/*
  Der Unterschied trifft auf, wenn das Ergebnis der Division negativ
  ist und sich dadurch das Ergebnis von floorDiv und normaler Integer
  Division unterscheidet.  Zum Beispiel: -3 / 2 = -1, -3 % 2 = -1,
  aber floorDiv(-3,2) = -2, floorMod(-3,2) muss dann 1 sein, damit a
  == floorDiv(a, b) * b + floorMod(a, b)
 */
i32 floorMod(i32 a, i32 b) {
	return ((sgn(a) + sgn(b)) || ((a % b) == 0)) != 0 ? a % b : a % b + b;
}

i32 floorDiv(i32 a, i32 b) {
	i32 c = (a % b) != 0 ? std::abs(b) : 0;
	return (sgn(a) + sgn(b)) != 0 ? a / b : -(std::abs(a) + c) / std::abs(b);
}

bool gap_year(i32 y) {
	return ((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0);
}

i32 weekday_helper(i32 d, i32 m, i32 y, i32 z) {
	i32 j1 = (365 * z + (z / 4) - (z / 100) + (z / 400)) % 7;
	i32 p =
		(m == 1) ? d : ((m == 2) ? d + 31
								 : (((m > 2) && !gap_year(y))
										? (d + 59 + ((153 * m - 457) / 5))
										: (d + 60 + ((153 * m - 457) / 5))));
	return (j1 + p - 1) % 7;
}

i32 weekday2001(i32 d, i32 m, i32 y) {
	i32 z = y - 2001;
	return weekday_helper(d, m, y, z);
}

/*
  Der Ablauf der Wochentage wiederholt sich, durch die Regeln zu
  Schaltjahren alle 400 Jahre, also kann jedes beliebige Vielefache
  von 400 + 1 gewählt werden, insbesondere 0 * 400 + 1 = 1
*/
i32 weekday1(i32 d, i32 m, i32 y) {
	i32 z = y - 1;
	return weekday_helper(d, m, y, z);
}

i32 weekday(i32 d, i32 m, i32 y) {
	i32 z  = y - 2001;
	i32 j1 = floorMod(
		365 * z + floorDiv(z, 4) - floorDiv(z, 100) + floorDiv(z, 400), 7);
	i32 p = (m == 1)
				? d
				: ((m == 2) ? d + 31
							: (((m > 2) && !gap_year(y))
								   ? (d + 59 + floorDiv((153 * m - 457), 5))
								   : (d + 60 + floorDiv((153 * m - 457), 5))));
	return (j1 + p - 1) % 7;
}

int main() {
	assert(weekday2001(1, 1, 2002) == 1);
	assert(weekday2001(7, 2, 2001) == 2);
	assert(weekday2001(12, 7, 2008) == 5);
	assert(weekday2001(28, 2, 2016) == 6);
	assert(weekday2001(10, 11, 2016) == 3);
	assert(weekday2001(10, 11, 2004) == 2);

	assert(weekday(1, 1, 2002) == 1);
	assert(weekday(7, 2, 2001) == 2);
	assert(weekday(12, 7, 2008) == 5);
	assert(weekday(28, 2, 2016) == 6);
	assert(weekday(10, 11, 2016) == 3);
	assert(weekday(10, 11, 2004) == 2);

	assert(weekday(28, 2, 2000) == 0);
	assert(weekday(29, 2, 2000) == 1);
	assert(weekday(1, 3, 2000) == 2);

	assert(weekday(27, 2, 1900) == 1);
	assert(weekday(28, 2, 1900) == 2);
	assert(weekday(1, 3, 1900) == 3);

	assert(weekday(28, 2, 1600) == 0);
	assert(weekday(29, 2, 1600) == 1);
	assert(weekday(1, 3, 1600) == 2);
	assert(weekday(3, 1, 1578) == 1);

	assert(weekday1(1, 1, 2002) == 1);
	assert(weekday1(7, 2, 2001) == 2);
	assert(weekday1(12, 7, 2008) == 5);
	assert(weekday1(28, 2, 2016) == 6);
	assert(weekday1(10, 11, 2016) == 3);
	assert(weekday1(10, 11, 2004) == 2);

	assert(weekday1(28, 2, 2000) == 0);
	assert(weekday1(29, 2, 2000) == 1);
	assert(weekday1(1, 3, 2000) == 2);

	assert(weekday1(27, 2, 1900) == 1);
	assert(weekday1(28, 2, 1900) == 2);
	assert(weekday1(1, 3, 1900) == 3);

	assert(weekday1(28, 2, 1600) == 0);
	assert(weekday1(29, 2, 1600) == 1);
	assert(weekday1(1, 3, 1600) == 2);
	assert(weekday1(3, 1, 1578) == 1);
}
