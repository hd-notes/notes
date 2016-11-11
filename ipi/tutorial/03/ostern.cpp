/*
  Copyright (C) 2016 by Robin Heinemann. All Rights Reserved.
  ostern.cpp -- Berechnung des Datum von Ostern nach Gauß Algirithmus
*/

#include "common.h"

str easter(i32 year) {
	i32 a = year % 19;
	i32 b = year % 4;
	i32 c = year % 7;
	i32 k = year / 100;
	i32 p = (8 * k + 13) / 25;
	i32 q = k / 4;
	i32 m = (15 + k - p - q) % 30;
	i32 d = (19 * a + m) % 30;
	i32 n = (4 + k - q) % 7;
	i32 e = (2 * b + 4 * c + 6 * d + n) % 7;
	i32 x = 22 + d + e;
	i32 z = (x == 57) ? 50 : (((x == 56) && (d == 28) && (a > 10)) ? 49 : x);
	return std::to_string((z < 32) ? z : z - 31) +
		   ((z < 32) ? ". März" : ". April");
}

int main() {
	assert(easter(2000) == "23. April");
	assert(easter(2001) == "15. April");
	assert(easter(2002) == "31. März");
	assert(easter(2003) == "20. April");
	assert(easter(2004) == "11. April");
	assert(easter(2005) == "27. März");
	assert(easter(2006) == "16. April");
	assert(easter(2007) == "8. April");
	assert(easter(2008) == "23. März");
	assert(easter(2009) == "12. April");
}
