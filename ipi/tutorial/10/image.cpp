/*
  Copyright (C) 2017 by Robin Heinemann. All Rights Reserved.
  image.cpp -- pnm image manipulation
*/

#include "image.hpp"
#include <cassert>
#include <iostream>

int main() {
    Image i(4, 3);
    assert(i.width() == 4);
    assert(i.height() == 3);

    for(int x = 0; x < i.width(); x++) {
        for(int y = 0; y < i.height(); y++) {
            assert(i(x, y) == 0);
        }
    }

	assert(to_string(i) == std::string("0 0 0 0\n0 0 0 0\n0 0 0 0\n"));

    for(int x = 0; x < i.width(); x++) {
        for(int y = 0; y < i.height(); y++) {
            i(x, y) = 255 * ((x + 1 + y % 2) % 2);
        }
	}
	std::cout << to_string(i); // == std::string("0 0 0 0\n0 0 0 0\n0 0 0 0\n")   }
}
